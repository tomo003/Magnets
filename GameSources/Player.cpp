#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(0.3f));
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.6f, 0.6f, 0.6f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.4f, 0.0f)
		);

		// BcPNTStaticModelDraw
		m_ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		//m_ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		//m_ptrDraw->SetMeshResource(L"Player01_MESH");
		m_ptrDraw->SetMeshResource(L"PlayerMotionfbx_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw->AddAnimation(L"RIGHT", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"LEFT", 30, 60, true, 30);
		m_ptrDraw->AddAnimation(L"FRONT", 60, 90, true, 30);
		m_ptrDraw->AddAnimation(L"BACK", 90, 120, true, 30);
		//m_ptrDraw->ChangeCurrentAnimation(L"LEFT");

		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//�J�������ǂ�������^�[�Q�b�g(�v���C���[)�̐ݒ�
			ptrCamera->SetTargetObj(GetThis<GameObject>());
		}
	}

	//�X�V����
	void Player::OnUpdate(){
		MovePlayer();
	}

	//�v���C���[�̓���
	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// �f���^�^�C���̎擾
		Vec3 pos = m_ptrTrans->GetPosition();//�v���C���[���W�̎擾

		auto device = app->GetInputDevice();//�R���g���[���[���W�̎擾
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (padLStick.length() > 0.0f) {
			pos = pos + padLStick * delta * m_speed;
		}
		m_ptrTrans->SetPosition(Vec3(pos));


		//auto KeyState = app->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPushKeyTbl['A']) {
		//	padLStick.x = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['D']) {
		//	padLStick.x = 1.0f;
		//}
		//else {
		//	padLStick.x = 0;
		//}


		if (padLStick.length() > 0.0f) {
			pos = pos + padLStick * delta * m_speed;
			if (padLStick.x > 0.0f) {
				AnimationPlayer(RIGHT);
			}
			else if (padLStick.x < 0.0f) {
				AnimationPlayer(LEFT);
			}
			else {
				AnimationPlayer(FRONT);
			}
		}

		limitSpeed();
		pos += m_Velocity * delta;
		m_Velocity.setAll(0);


		m_ptrTrans->SetPosition(Vec3(pos));

		//�W�����v����
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				JumpPlayer();
				jumpCount--;
			}
		}
		else if (pos.y <= -0.4f) {
			jumpCount = 1;
		}

		//�����؂�ւ�
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			count++;
			count = count % 3;
			switch (count){
			case 0:
				m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");
				break;
			case 1:
				m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");
				break;
			default:
				m_ptrDraw->SetMeshResource(L"PlayerMotionfbx_MESH");
				break;
			}
			
		}

	}

	//�W�����v�֐�
	void Player::JumpPlayer() {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(Vec3(0.0f, 5.0f, 0.0f));
	}

	//�A�j���[�V�����֐�
	void Player::AnimationPlayer(eMotion Motion) {

		//�A�j���[�V�����ύX
		m_currentMotion = Motion;

		// ���[�V�����̃^�C�v���ς���Ă�����
		if (m_currentMotion != m_pastMotion || m_ptrDraw->GetCurrentAnimation() != m_motionKey.at(m_currentMotion))
		{
			// �^�C�v�ɉ����ă��[�V������ύX����
			m_ptrDraw->ChangeCurrentAnimation(m_motionKey.at(m_currentMotion));
			m_pastMotion = m_currentMotion;
		}
		float delat = App::GetApp()->GetElapsedTime();

		switch (m_currentMotion){
		case RIGHT:
			m_ptrDraw->UpdateAnimation(delat * 1.0f);
			break;
		case LEFT:
			m_ptrDraw->UpdateAnimation(delat * 1.0f);
			break;
		default:
			m_ptrDraw->UpdateAnimation(delat * 0.0f);
			break;
		}
	}

	// �v���C��[�Ɉ��͂�K�p
	void Player::ApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<MagnetsObject>(L"MagnetsObject");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = ptrMagObj->GetMass();
		float objAreaRadius = ptrMagObj->GetAreaRadius();

		auto playerPos = m_ptrTrans->GetPosition();

		Vec3 direction = objPos - playerPos;
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
		Vec3 force = (direction / distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force;
	}

	// �v���C��[�ɐ˗͂�K�p
	void Player::ApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<MagnetsObject>(L"MagnetsObject");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = ptrMagObj->GetMass();

		auto playerPos = m_ptrTrans->GetPosition();

		Vec3 direction = objPos - playerPos;
		float distance = max(sqrtf(direction.x * direction.x + direction.y * direction.y), 1.0f);
		Vec3 force = (direction / distance) * REPEL_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force * -1;
	}


	// ���x�𐧌�
	void Player::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (speed > MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * MAX_SPEED;
		}
	}


	//void Player::OnUpdate2() {
	//	auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
	//	wstring fpsStr(L"FPS: ");
	//	fpsStr += Util::UintToWStr(fps);
	//	auto ptrString = GetComponent<StringSprite>();
	//	ptrString->SetText(fpsStr);
	//}
}
//end basecross

