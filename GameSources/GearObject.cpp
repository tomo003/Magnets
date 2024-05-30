#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GearObject::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.20f, 0.1f),
			Vec3(0.0f),
			Vec3(0.0f),
			Vec3(0.0f)
		);

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"GearObject_MESH");
		//m_ptrDraw->SetTextureResource(L"GRAY_TX");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		auto CollComp = AddComponent<CollisionSphere>();
		CollComp->SetFixed(true);
		CollComp->SetDrawActive(true);

		m_TransComp = GetComponent<Transform>();
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(Vec3(8.0f));
		m_TransComp->SetRotation(Vec3(0.0f));

		//SetAlphaActive(true);

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");

	}

	void GearObject::OnUpdate() {
		float delta = App::GetApp()->GetElapsedTime();

		m_Rotation.z += delta;

		m_TransComp->SetRotation( m_Rotation);
	}


	void GearObjFloor::OnCreate() {

	}

	//void GearObjFloor::ApplyForcePlayer() {
	//	auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
	//	Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
	//	int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
	//	int objMagPole = static_cast<int>(m_eMagPole);

	//	auto direction = ABSV(playerPos, m_position);
	//	float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

	//	if (distance < m_MagAreaRadius) {
	//		if (playerMagPole == -1) {
	//			return;
	//		}
	//		else {
	//			ptrPlayer->ApplyAttraction(GetThis<GameObject>());
	//		}
	//	}
	//}


}