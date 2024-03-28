#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player2::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(1.0f));
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 5.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.25f, 1.25f, 1.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		// BcPNTStaticModelDraw
		m_ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		m_ptrDraw->SetMeshResource(L"Player2Brack_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw->AddAnimation(L"RIGHT", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"LEFT", 30, 60, true, 30);
		m_ptrDraw->AddAnimation(L"FRONT", 60, 90, true, 30);
		m_ptrDraw->AddAnimation(L"BACK", 90, 120, true, 30);
		//m_ptrDraw->ChangeCurrentAnimation(L"LEFT");

		AddTag(L"Player2");
	}

	//�X�V����
	void Player2::OnUpdate() {
		MovePlayer();
		ApplyForcePlayer();

		Vec3 pos = m_ptrTrans->GetPosition();
		if (pos.y < -5.0f) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	//�v���C���[�̓���
	void Player2::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// �f���^�^�C���̎擾
		Vec3 pos = m_ptrTrans->GetPosition();//�v���C���[���W�̎擾

		auto device = app->GetInputDevice();//�R���g���[���[���W�̎擾
		auto pad = device.GetControlerVec()[1];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (padLStick.length() > 0.0f) {
			pos = pos + padLStick * delta * m_speed;
		}
		m_ptrTrans->SetPosition(Vec3(pos));

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

		if (pos.y < -5.0f) {
			DeathPlayer();
		}


		//�����؂�ւ�
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			switch (m_eMagPole) {
			case EState::eFalse:
				m_ptrDraw->SetMeshResource(L"Player2Red_MESH");//N��
				m_eMagPole = EState::eN;
				break;
			case EState::eN:
				m_ptrDraw->SetMeshResource(L"Player2Blue_MESH");//S��
				m_eMagPole = EState::eS;
				break;
			case EState::eS:
				m_ptrDraw->SetMeshResource(L"Player2Brack_MESH");//����
				m_eMagPole = EState::eFalse;
				break;
			}

		}

	}

	//�W�����v�֐�
	void Player2::JumpPlayer() {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(Vec3(0.0f, 5.0f, 0.0f));
	}

	//���S�֐�
	void Player2::DeathPlayer() {
		PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	}


	//�A�j���[�V�����֐�
	void Player2::AnimationPlayer(eMotion Motion) {

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

		switch (m_currentMotion) {
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
	void Player2::ApplyAttraction() {
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

	void Player2::PlayerApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = 1.0f;
		float objAreaRadius = 3.0f;

		auto playerPos = m_ptrTrans->GetPosition();

		Vec3 direction = objPos - playerPos;
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
		Vec3 force = (direction / distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force;
	}

	// �v���C��[�ɐ˗͂�K�p
	void Player2::ApplyRepulsion() {
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
	void Player2::PlayerApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = 1.0f;

		auto playerPos = m_ptrTrans->GetPosition();

		Vec3 direction = objPos - playerPos;
		float distance = max(sqrtf(direction.x * direction.x + direction.y * direction.y), 1.0f);
		Vec3 force = (direction / distance) * REPEL_CONSTANT * m_playerMass * objMass / (distance * distance);
		m_Velocity += force * -1;
	}

	void Player2::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_ptrTrans->GetPosition());
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < 3.0f) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->PlayerApplyRepulsion();
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->PlayerApplyAttraction();
			}// ptrPlayer->ApplyAttraction();

		}
	}


	// ���x�𐧌�
	void Player2::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (speed > MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * MAX_SPEED;
		}
	}


}
//end basecross
