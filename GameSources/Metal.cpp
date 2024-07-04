/*!
@file Metal.cpp
@brief 金属オブジェクト
@autor 
@detail ゴールオブジェクトやその周辺のオブジェクトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Metal::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"METAL_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eMetal;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius);
		ptrArea->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
	}

	void Metal::OnUpdate()
	{
		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void Metal::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		// プレイヤー１が一定の距離に入ったら
		if (distance < m_MagAreaRadius) {
			// プレイヤー１が磁力のない状態だったら
			if (playerMagPole == -1) {
				return;
			}
			else {
				// 引力の呼び出し
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}
		}
	}
	void Metal::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		// プレイヤー２が一定の距離に入ったら
		if (distance < m_MagAreaRadius) {
			// プレイヤー２が磁力のない状態だったら
			if (playerMagPole == -1) {
				return;
			}
			else {
				// 引力の呼び出し
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}
		}
	}
}