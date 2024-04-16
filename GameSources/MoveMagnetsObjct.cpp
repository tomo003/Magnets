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

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(2.0f, 0.75f, 0.75f);

		m_ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");
		auto m_AreaTransComp = m_ptrArea->GetComponent<Transform>();
		m_AreaTransComp->SetParent(GetThis<MoveMetalObject>());
	}

	void MoveMetalObject::OnUpdate() {
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// �f���^�^�C��(�O�t���[������̌o�ߎ���)���擾����
		float delta = app->GetElapsedTime();

		static float a = 0.0f; // 0 �` 1�̌W��(0 - 100%)

		const Vec3 start = m_points[m_currentPointIndex % m_points.size()];
		const Vec3 end = m_points[(m_currentPointIndex + 1) % m_points.size()];
		Vec3 pos = Utility::Lerp(start, end, a); // ���삵�����`��Ԋ֐�
		a += m_speed * delta / (end - start).length(); // end - start��2�_�Ԃ����ԃx�N�g���B���̒����́u2�_�Ԃ̋����v�ƂȂ�
		if (a >= 1.0f)
		{
			m_currentPointIndex++;
			a = 0.0f;
		}

		//Vec3 pos = m_transform->GetPosition(); // ���݂̍��W���擾����
		m_ptrTrans->SetPosition(pos); // �V�������W�ōX�V����

		ApplyForcePlayer();
		//m_ptrArea->UpdateArea(m_position);
	}

	// �v���C���[�Ɏ��͂ɂ��͂�K�p
	void MoveMetalObject::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == -1) {
				return;
			}
			else {
				ptrPlayer->ApplyAttraction();
			}

		}
	}

}