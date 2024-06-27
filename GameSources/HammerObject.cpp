#include "stdafx.h"
#include "Project.h"

#define PIDIV3 (XM_PIDIV4 * 1.5f) // ��/2�ƃ�/4�̊�

namespace basecross {
	void HammerPressArea::OnCreate()
	{
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(2.0f, 0.5f, 0.25f);
		m_TransComp->SetPosition(m_position.x, m_position.y - 0.25f, m_position.z-0.375f);
		
		m_ptrPlayerF = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_PlayerFScaleHelf = m_ptrPlayerF->GetComponent<Transform>()->GetScale() / 2;
		m_ptrPlayerS = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		m_PlayerSScaleHelf = m_ptrPlayerS->GetComponent<Transform>()->GetScale() / 2;

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		if(m_eMagPole == EState::eN)
		{
			m_DrawComp->SetTextureResource(L"REDAREA_TX");
		}
		if (m_eMagPole == EState::eS)
		{
			m_DrawComp->SetTextureResource(L"BULEAREA_TX");
		}
		if (m_eMagPole == EState::eFalse)
		{
			m_DrawComp->SetTextureResource(L"WHITEAREA_TX");
		}
		SetAlphaActive(true);
	}

	/** @brief Player���͈͓��ɂ��邩�𔻒肷��֐�(Player1�p)
	*   @param �����Ȃ�
	*   @return bool Player���͈͓��ɂ�����true
	*/
	bool HammerPressArea::AreaInPlayerF() {
		m_PlayerFPos = m_ptrPlayerF->GetComponent<Transform>()->GetWorldPosition();
		
		if (m_PlayerFPos.x <= m_AreaRightLimit && // �v���C���[���n���}�[�G���A�̉E������
			m_PlayerFPos.x >= m_AreaLeftLimit) // �v���C���[���n���}�[�G���A�̍�������
		{
			return true; // �����Ȃ̂�true
		}
		return false;
		
	}
	/** @brief Player���͈͓��ɂ��邩�𔻒肷��֐�(Player2�p)
	*   @param �����Ȃ�
	*   @return bool Player���͈͓��ɂ�����true
	*/
	bool HammerPressArea::AreaInPlayerS() {
		m_PlayerSPos = m_ptrPlayerS->GetComponent<Transform>()->GetWorldPosition();

		if (m_PlayerSPos.x <= m_AreaRightLimit && // �v���C���[���n���}�[�G���A�̉E������
			m_PlayerSPos.x >= m_AreaLeftLimit) // �v���C���[���n���}�[�G���A�̍�������
		{
			return true; // �����Ȃ̂�true
		}
		return false;

	}


	void HammerObject::OnCreate() {
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(m_Scale);
		m_position = m_CreatePos + m_posDiff;
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetPivot(0.0f, -m_PivotLength, 0.0f);
		m_TransComp->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		m_CollComp = AddComponent<CollisionObb>();
		m_CollComp->SetAfterCollision(AfterCollision::None);
		//m_CollComp->SetFixed(true);
		//m_CollComp->SetDrawActive(true);
		
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 0.3f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.75f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTBoneModelDraw>();
		switch (m_eMagPole)
		{
		case EState::eFalse:
			m_DrawComp->SetMeshResource(L"Hammer_Black_MESH");
			break;
		case EState::eN:
			m_DrawComp->SetMeshResource(L"Hammer_Red_MESH");
			break;
		case EState::eS:
			m_DrawComp->SetMeshResource(L"Hammer_Blue_MESH");
			break;
		case EState::eMetal:
			m_DrawComp->SetMeshResource(L"Hammer_Black_MESH");
			break;
		default:
			break;
		}
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		m_ptrPressArea = GetStage()->AddGameObject<HammerPressArea>(m_CreatePos, m_eMagPole);
		if (m_eMagPole != EState::eFalse) {
			m_MagArea = GetStage()->AddGameObject<MagnetArea>(Vec3(m_position.x, m_position.y, m_position.z + m_Scale.z / 2), m_MagAreaRadius);
		}

		m_ptrPlayerF = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_ptrPlayerS = GetStage()->GetSharedGameObject<Player2>(L"Player2");

		m_ptrAudio = App::GetApp()->GetXAudio2Manager();
	}

	void HammerObject::OnUpdate() {
		// �n���}�[�̓���؂�ւ�
		switch (m_MoveState)
		{
		case HammerMoveState::Remove:
			RemoveHammer();
			break;

		case HammerMoveState::Stop:
			StopHammer(m_lastMoveState);
			break;

		case HammerMoveState::Antic:
			AnticHammer();
			break;

		case HammerMoveState::Swing:
			SwingHammer();
			break;

		default:
			break;
		}
			MagAreaCorrection();
	}

	// �����߂�
	void HammerObject::RemoveHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// ���Ԃ̎擾
		
		auto rad = Utility::DegToRad(m_SwingVal);
		m_Rotation.x += delta * rad;
		m_TransComp->SetRotation(m_Rotation.x, 0.0f, 0.0f);

		if (m_Rotation.x >= 0.0f) { // �O�x�Ŏ~�߂�
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Stop;
			SetStopTime(m_ResetStopTime);
		}
	}

	// ��~
	void HammerObject::StopHammer(const HammerMoveState& lastState) {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// ���Ԃ̎擾
		m_CurrentTime += delta;

		if ((!isSEActive) && (m_lastMoveState == HammerMoveState::Swing))
		{
			m_ptrAudio->Start(L"HAMMER_SE", 0, 1.0f);
			isSEActive = true;
		}

		// �o�ߎ��Ԃ��ݒ肵�����Ԃ��z������
		if (m_CurrentTime >= m_StopTime)
		{
			ResetCurrentTime(); // �o�ߎ��Ԃ����Z�b�g

			// ��O�̓���ɂ���Đ؂�ւ�
			switch (m_lastMoveState)
			{
			// Remove(�߂�Ȃ�)
			case HammerMoveState::Remove:
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Antic;// �\�������
				break;

			// ��~�̌�ɒ�~�͖����̂�break
			case HammerMoveState::Stop:
				break;

			// �\������̌�ɒ�~�͖����̂�break
			case HammerMoveState::Antic:
				break;

			// Swing(�U�艺�낵�Ȃ�)
			case HammerMoveState::Swing:
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // �߂��
				break;

			default:
				break;
			}
			isSEActive = false;
		}
		return;
	}

	// �\������
	void HammerObject::AnticHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// ���Ԃ̎擾

		m_CurrentTime += delta;

		if (m_CurrentTime <= 1.0f) // 1�b��
		{
			// �k�킹��
			AnticTremble(delta);
		}
		else if (m_CurrentTime <= 2.0f) // �P�b��
		{
			m_position = m_CreatePos + m_posDiff; // �����ʒu�ɖ߂�
			m_TransComp->SetPosition(m_position);
			return; // �������Ȃ�(�ꎞ��~)
		}
		else 
		{
			ResetCurrentTime();
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Swing; // �U�艺�낵��
			ChangeFixed(false);
		}
	}
	// �\������̐U��
	void HammerObject::AnticTremble(const float& time) {

		// X���W���U�ꕝ�̉E�[�����[�Ȃ�
		if (m_position.x >= m_TrembleRightX || m_position.x <= m_TrembleLeftX) 
		{
			m_TrembleDir *= -1; // �������]
		}
		m_position.x += time * m_TrembleDir * m_TrembleSpeed;
		m_TransComp->SetPosition(m_position);
	}

	// �U�艺�낵
	void HammerObject::SwingHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// ���Ԃ̎擾

		auto rad = Utility::DegToRad(m_SwingVal);
		m_Rotation.x -= delta * rad * m_SwingSpeed;
		m_TransComp->SetRotation(m_Rotation.x, 0.0f, 0.0f);

		// ��60�x�t�߂̂Ƃ�
		if (m_Rotation.x <= -PIDIV3) {
			SwingingPlayerCheck();
		}
		if (m_Rotation.x <= -XM_PIDIV2) { // 90�x�Ŏ~�߂�
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Stop;
			SetStopTime(m_SwingStopTime);
			ChangeFixed(true);
		}
	}
	// �U�艺�낵�̎���Player��������
	void HammerObject::SwingingPlayerCheck(){
		if (m_ptrPressArea->AreaInPlayerF()) // �G���A����Player1������Ƃ�
		{
			int playerFMag = int(m_ptrPlayerF->GetPlayerMagPole());
			if (int(m_eMagPole) == playerFMag && playerFMag != STATE_NONE) { // �����̎��ɂƔ͈͓���player�̎��ɂ������Ȃ�
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // ���˕Ԃ�(�߂�)
				SetStopTime(m_SwingStopTime * 1.5f); // ���˕Ԃ������̂ݎ��Ԃ�1.5�{��
				ChangeFixed(true);
				return;
			}
		}

		if (m_ptrPressArea->AreaInPlayerS()) // �G���A����Player2������Ƃ�
		{
			int playerSMag = int(m_ptrPlayerS->GetPlayerMagPole());
			if (int(m_eMagPole) == playerSMag && playerSMag != STATE_NONE) { // �����̎��ɂƔ͈͓���player�̎��ɂ������Ȃ�
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // ���˕Ԃ�(�߂�)
				SetStopTime(m_SwingStopTime * 1.5f); // ���˕Ԃ������̂ݎ��Ԃ�1.5�{��
				ChangeFixed(true);
				return;
			}
		}
	}

	// �U�艺�낵���Ƃ���Player���������̐ڐG����
	void HammerObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrPlayerF = dynamic_pointer_cast<Player>(Other); // �I�u�W�F�N�g�擾
		auto ptrPlayerS = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayerF) {
			m_ptrPlayerF->PlayerDeath();
		}
		if (ptrPlayerS) {
			m_ptrPlayerS->PlayerDeath();
		}
	}

	// ���̓G���A�̈ʒu�␳
	void HammerObject::MagAreaCorrection() {

		// ���ɂ�������΂���ȍ~�͖���
		if (!m_MagArea) return;

		auto MagAreaTrans = m_MagArea->GetComponent<Transform>();
		Vec3 MagAreaPos = MagAreaTrans->GetWorldPosition();
		float diff = m_Rotation.x / XM_PIDIV2 * m_PivotLength;
		MagAreaTrans->SetPosition(MagAreaPos.x, m_position.y + diff, MagAreaPos.z);
	}
}