#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, true)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, true)
#define COL_PURPLE Col4(0.56f, 0.42f, 0.78f, true)

namespace basecross {
	void MoveMetalObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetTextureResource(L"GRAY_TX");
		m_ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(2.0f, 0.75f, 0.75f);

		m_ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius);
		auto m_AreaTransComp = m_ptrArea->GetComponent<Transform>();
		m_AreaTransComp->SetParent(GetThis<MoveMetalObject>());
		//m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_position.x, m_position.y, m_position.z + (m_ptrTrans->GetScale().z / 2)), Vec3(1.0f), L"MagneticRange");
	}

	void MoveMetalObject::OnUpdate() {
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// �f���^�^�C��(�O�t���[������̌o�ߎ���)���擾����
		float delta = app->GetElapsedTime();

		const Vec3 start = m_points[m_currentPointIndex % m_points.size()];
		const Vec3 end = m_points[(m_currentPointIndex + 1) % m_points.size()];
		Vec3 pos = Utility::Lerp(start, end, m_ratio); // ���삵�����`��Ԋ֐�
		m_ratio += m_speed * delta / (end - start).length(); // end - start��2�_�Ԃ����ԃx�N�g���B���̒����́u2�_�Ԃ̋����v�ƂȂ�
		if (m_ratio >= 1.0f)
		{
			m_currentPointIndex++;
			m_ratio = 0.0f;
		}

		//Vec3 pos = m_transform->GetPosition(); // ���݂̍��W���擾����
		m_ptrTrans->SetPosition(pos); // �V�������W�ōX�V����

		ApplyForcePlayer();
		ApplyForceSecondPlayer();
		//m_ptrArea->UpdateArea(m_position);

		/*Vec3 position = m_ptrTrans->GetPosition();*/
		m_efk->SetLocation(Vec3(pos.x, pos.y, pos.z + (m_ptrTrans->GetScale().z / 2)));
	}

	// �v���C���[�Ɏ��͂ɂ��͂�K�p
	void MoveMetalObject::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == -1) {
				return;
			}
			else {
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}
		}
	}

	// �v���C���[�Ɏ��͂ɂ��͂�K�p
	void MoveMetalObject::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == -1) {
				return;
			}
			else {
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}
		}
	}

	void MoveMetalObject::EfkStop() {
		m_efk->StopEffect();
	}
	void MoveMetalObject::OnDestroy() {
		EfkStop();
	}

	void MoveFloorButton::OnCreate() {
		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CYLINDER");
		m_DrawComp->SetTextureResource(L"MOVEFLOOR_TX");
		m_DrawComp->SetOwnShadowActive(true);
		//m_DrawComp->SetEmissive(Col4(0.0f, 1.0f, 0.0f, 1.0f));

		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(m_scale);

		//auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
		auto CollComp = AddComponent<CollisionObb>();
		//CollComp->AddExcludeCollisionGameObject(ptrMoveFloor);

		SetUp();
	}

	void MoveFloorButton::OnUpdate() {
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();
		// �f���^�^�C��(�O�t���[������̌o�ߎ���)���擾����
		float delta = app->GetElapsedTime();

		m_TransComp->SetPosition(m_startPos.x, m_startPos.y, m_startPos.z); // �V�������W�ōX�V����

		// �����ʒu�A��~�ʒu���z����Ȃ�X�e�[�g���~�ɐ؂�ւ�
		//if (m_position.y < m_endPosY || m_position.y > m_startPos.y) {
		//	eMoveState = EMoveState::eStop;
		//}
	}


	void MoveFloorButton::OnCollisionEnter(const CollisionPair& Pair) {
		const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
		const Vec3& hitPoint = Pair.m_CalcHitPoint; // �Փˈʒu(Vec3)

		if (other->FindTag(L"Player")) {
			eMoveState = EMoveState::eMove;

			auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
			ptrMoveFloor->FloorActive(true);
		}
	}

	void MoveFloorButton::OnCollisionExcute(const CollisionPair& Pair) {
		const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
		const Vec3& hitPoint = Pair.m_CalcHitPoint; // �Փˈʒu(Vec3)
	}

	void MoveFloorButton::OnCollisionExit(const CollisionPair& Pair) {
		const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
		const Vec3& hitPoint = Pair.m_CalcHitPoint; // �Փˈʒu(Vec3)

		if (other->FindTag(L"Player")) {
			eMoveState = EMoveState::eReMove;

			auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
			ptrMoveFloor->FloorActive(false);
		}
	}

	void MoveFloor::OnCreate()
	{
		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		m_DrawComp->SetTextureResource(L"MOVEFLOOR_TX");
		m_DrawComp->SetOwnShadowActive(true);

		auto CollComp = AddComponent<CollisionObb>();
		CollComp->SetFixed(true);
		//auto ptrMoveFloorButton = GetStage()->GetSharedGameObject<MoveFloorButton>(L"MoveFloorButton");
		//CollComp->AddExcludeCollisionGameObject(ptrMoveFloorButton);

		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(m_scale);

		m_actionComp = AddComponent<Action>();

		SetUp();
	}

	void MoveFloor::OnUpdate() {
		FloorMovePattern();

		// �����ʒu�A��~�ʒu���z����Ȃ�X�e�[�g���~�ɐ؂�ւ�
		if (m_position.x < m_endPos.x || m_position.x > m_startPos.x) {
			eMoveState = EMoveState::eStop;
		}
	}

	/**
	* @fn void FloorMovePattern()
	* @brief �ړ����̏�Ԃɏ]���ē���؂�ւ�����֐�
	* @param �����Ȃ�
	* @return �߂�l�Ȃ�
	* @details eMoveState(�ړ����̏��)�ɂ���ē����؂�ւ��A�ʒu���X�V����
	*/
	void MoveFloor::FloorMovePattern() {
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();
		// �f���^�^�C��(�O�t���[������̌o�ߎ���)���擾����
		float delta = app->GetElapsedTime();

		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		// �ړ����̏�Ԃɏ]���ē���؂�ւ�
		switch (eMoveState)
		{
		case EMoveState::eReMove: // ReMove�Ȃ�߂�
			m_position -= m_MoveDir * m_speed * delta;
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 2.0f);
				MoveSEPlay = true;
			}
			break;
		case EMoveState::eStop: // Stop�Ȃ��~(�������Z���Ȃ�)
			XAPtr->Stop(m_kadouonn);
			MoveSEPlay = false;
			break;
		case EMoveState::eMove: // Move�Ȃ�ړ�
			m_position += m_MoveDir * m_speed * delta;
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 2.0f);
				MoveSEPlay = true;
			}
			break;
		default:
			break;
		}
		m_TransComp->SetPosition(m_position); // �V�������W�ōX�V����

	}

	void MoveFloor::ResetAll() {
		m_TransComp->SetPosition(m_startPos);
	}
}