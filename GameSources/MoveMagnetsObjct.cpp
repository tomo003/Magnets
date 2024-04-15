#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, true)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, true)
#define COL_PURPLE Col4(0.56f, 0.42f, 0.78f, true)

namespace basecross {
	void MoveMagnetsObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetEmissive(COL_RED);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(2.0f, 0.75f, 0.75f);

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");
		m_points = {
			Vec3(+3.5f, m_position.y, 0.0f), // 左
			Vec3(-3.5f, m_position.y, 0.0f) // 右
		};

	}

	void MoveMagnetsObject::OnUpdate() {
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		static float a = 0.0f; // 0 〜 1の係数(0 - 100%)

		const Vec3 start = m_points[m_currentPointIndex % m_points.size()];
		const Vec3 end = m_points[(m_currentPointIndex + 1) % m_points.size()];
		Vec3 pos = Utility::Lerp(start, end, a); // 自作した線形補間関数
		a += m_speed * delta / (end - start).length(); // end - startは2点間を結ぶベクトル。その長さは「2点間の距離」となる
		if (a >= 1.0f)
		{
			m_currentPointIndex++;
			a = 0.0f;
		}

		//Vec3 pos = m_transform->GetPosition(); // 現在の座標を取得する
		m_ptrTrans->SetPosition(pos); // 新しい座標で更新する

		ApplyForcePlayer();
	}

	// プレイヤーに磁力による力を適用
	void MoveMagnetsObject::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole * objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->ApplyRepulsion();
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttraction();
			}// ptrPlayer->ApplyAttraction();

		}
	}

}