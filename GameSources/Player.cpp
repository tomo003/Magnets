#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(1.0f));
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
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
	}

	//�X�V����
	void Player::OnUpdate(){
		MovePlayer();
	}

	//�v���C���[�̓���
	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// �f���^�^�C���̎擾
		m_pos = m_ptrTrans->GetPosition();//�v���C���[���W�̎擾

		auto device = app->GetInputDevice();//�R���g���[���[���W�̎擾
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (padLStick.length() > 0.0f) {
			m_pos = m_pos + padLStick * delta * m_speed;
		}
		m_ptrTrans->SetPosition(Vec3(m_pos));


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
			if (padLStick.x > 0.0f) {
				AnimationPlayer(RIGHT);
			}
			else if (padLStick.x < 0.0f) {
				AnimationPlayer(LEFT);
			}
		}
		else {
			AnimationPlayer(FRONT);
		}

		//�W�����v����
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				JumpPlayer();
				jumpCount--;
			}
		}
		else if (m_pos.y <= -0.4f) {
			jumpCount = 1;
		}

		//�����؂�ւ�
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			switch (m_eMagPole){
			case EState::eFalse:
				m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");//N��
				m_eMagPole = EState::eN;
				break;
			case EState::eN:
				m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");//S��
				m_eMagPole = EState::eS;
				break;
			case EState::eS:
				m_ptrDraw->SetMeshResource(L"PlayerMotionfbx_MESH");//����
				m_eMagPole = EState::eFalse;
				break;
			}
			
		}

		limitSpeed();
		m_pos += m_Velocity * delta;
		m_ptrTrans->SetPosition(Vec3(m_pos));
		m_Velocity.setAll(0);

	}

	//�W�����v�֐�
	void Player::JumpPlayer() {
		m_gravityComp = GetComponent<Gravity>();
		m_gravityComp->StartJump(Vec3(0.0f, 5.0f, 0.0f));
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
		auto ptrMagObj = GetStage()->GetSharedGameObject<MoveMetalObject>(L"MagnetsObject");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = ptrMagObj->GetMass();
		float objAreaRadius = ptrMagObj->GetAreaRadius();

		m_pos= m_ptrTrans->GetPosition();

		Vec3 direction = objPos - m_pos;
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
		Vec3 force = (direction / distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force;
	}

	// �v���C��[�ɐ˗͂�K�p
	void Player::ApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<MoveMetalObject>(L"MagnetsObject");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = ptrMagObj->GetMass();

		m_pos = m_ptrTrans->GetPosition();

		Vec3 direction = objPos - m_pos;
		float distance = max(sqrtf(direction.x * direction.x + direction.y * direction.y), 1.0f);
		Vec3 force = (direction / distance) * REPEL_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force * -1;
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrMagnets = dynamic_pointer_cast<MoveMetalObject>(Other); // �I�u�W�F�N�g�擾
		//auto magDir = GetMsgnetsDirection().second;
		if (ptrMagnets && (m_eMagPole != EState::eFalse)) // �`�F�b�N
		{
			m_gravityTemp = m_gravityComp->GetGravity();
			m_gravityComp->SetGravityZero();

			m_ptrTrans->SetParent(ptrMagnets);
		}
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		auto ptrMagnets = dynamic_pointer_cast<MoveMetalObject>(Other); // �I�u�W�F�N�g�擾
		if (ptrMagnets && (m_eMagPole == EState::eFalse)) // �`�F�b�N
		{
			m_gravityComp->SetGravity(m_gravityTemp);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		auto ptrMagnets = dynamic_pointer_cast<MoveMetalObject>(Other); // �I�u�W�F�N�g�擾
		if (ptrMagnets) // �`�F�b�N
		{
			m_gravityComp->SetGravity(m_gravityTemp);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}

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

