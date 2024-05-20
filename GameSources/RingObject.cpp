#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void RingObject::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.15f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"RingObject_MESH");
		//m_ptrDraw->SetTextureResource(L"GRAY_TX");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		auto CollComp = AddComponent<CollisionSphere>();
		CollComp->SetFixed(true);
		//CollComp->SetDrawActive(true);

		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(Vec3(3.0f));
		m_TransComp->SetRotation(0.0f, 0.0f, 0.0f);

		SetAlphaActive(true);

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");

	}

	void RingObject::OnUpdate() {
		ApplyForcePlayer();
	}

	void RingObject::ApplyForcePlayer() {
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
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}
		}
	}

}