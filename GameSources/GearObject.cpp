#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GearObject::OnCreate()
	{
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.1f),
			Vec3(0.0f),
			Vec3(0.0f),
			Vec3(0.0f)
		);

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"GearObject_MESH");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		m_TransComp = GetComponent<Transform>();
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(Vec3(7.0f));
		m_TransComp->SetRotation(m_Rotation);

		// ����ǉ����Đe�q�t��
		m_ptrGearFloorF = GetStage()->AddGameObject<GearObjFloor>(Vec3(m_position.x, m_position.y + 4.0f, 0.0f), m_RotSpeed, m_RotDir);
		m_ptrGearFloorF->GetComponent<Transform>()->SetParent(GetThis<GearObject>());
		m_ptrGearFloorS = GetStage()->AddGameObject<GearObjFloor>(Vec3(m_position.x, m_position.y - 4.0f, 0.0f), m_RotSpeed, m_RotDir);
		m_ptrGearFloorS->GetComponent<Transform>()->SetParent(GetThis<GearObject>());

	}

	void GearObject::OnUpdate() {
		// ��b�Ԃ�50�x��]������
		float delta = App::GetApp()->GetElapsedTime();
		m_Rotation.z += Utility::DegToRad(m_RotSpeed) * delta * m_RotDir;
		m_TransComp->SetRotation(m_Rotation);
	}


	void GearObjFloor::OnCreate() {
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetTextureResource(L"METAL_TX");
		m_ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(m_Scale);

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");
		auto m_AreaTransComp = ptrArea->GetComponent<Transform>();
		m_AreaTransComp->SetParent(GetThis<GearObjFloor>());
	}

	void GearObjFloor::OnUpdate() {
		RotToCenter();

		m_position = m_ptrTrans->GetWorldPosition();

		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void GearObjFloor::RotToCenter() {
		// �e�q�t�����Ă�Ɖ�]���e�ɉe������邽�ߓ�����]�ʂŐe�̔��Ό����ɉ�
		float delta = App::GetApp()->GetElapsedTime();
		m_Rotation.z -= Utility::DegToRad(m_RotSpeed) * delta * m_RotDir;
		m_ptrTrans->SetRotation(m_Rotation);
	}

	void GearObjFloor::ApplyForcePlayer() {
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

	void GearObjFloor::ApplyForceSecondPlayer() {
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

	//void GearObjFloor::OnCollisionEnter(const CollisionPair& Pair) {
	//	const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
	//	const Vec3& hitPoint = Pair.m_CalcHitPoint; // �Փˈʒu(Vec3)

	//	if (other->FindTag(L"Player")) {
	//		other->GetComponent<Transform>()->SetParent(GetThis<GearObjFloor>());
	//	}
	//}

	void GearObjFloor::EfkStop() {
		m_efk->StopEffect();
	}
	void GearObjFloor::OnDestroy() {
		EfkStop();
	}

}