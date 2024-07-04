/*!
@file DeathEffect.cpp
@brief 死亡時のエフェクト
@autor 吉田鈴
@detail プレイヤーの死亡時に出る飛び散るエフェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void DeathEffectImg::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックスs
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"DEATHEFFECT");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(2);
	}

	void DeathEffectImg::OnUpdate()
	{
		// アプリケーションオブジェクトへの参照を取得する
		auto& app = App::GetApp();

		// デルタタイムを取得する
		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		m_sec += delta * m_moveSpeed;
		auto scl = Vec3(pow(sin(m_sec + sin(m_sec + sin(m_sec * 2))), 2));
		transComp->SetScale(scl);
	}

	void DeathEffect::OnCreate()
	{
		m_ptrPlayerF = dynamic_pointer_cast<Player>(m_owner);
		m_ptrPlayerS = dynamic_pointer_cast<Player2>(m_owner);

		// この関数を呼んだのがプレイヤー１だったら
		if (m_ptrPlayerF)
		{
			m_ptrOwnerTrans = m_ptrPlayerF->GetComponent<Transform>();
		}
		// この関数を呼んだのがプレイヤー２だったら
		else if (m_ptrPlayerS)
		{
			m_ptrOwnerTrans = m_ptrPlayerS->GetComponent<Transform>();
		}

		// DeathEffectImgの生成
		for (int i = 0; i < 8;i++)
		{
			ptrEffect[i] = GetStage()->AddGameObject<DeathEffectImg>(Vec3(1.0f), m_ptrOwnerTrans->GetWorldPosition());
			m_startPos = m_ptrOwnerTrans->GetWorldPosition();
		}

		SetAlphaActive(true);
	}

	void DeathEffect::OnUpdate()
	{
		// アプリケーションオブジェクトへの参照を取得する
		auto& app = App::GetApp();

		// デルタタイムを取得する
		float delta = app->GetElapsedTime();

		m_time -= delta;
		// 一定時間たつまでループ
		if (m_time > 0)
		{
			for (int i = 0;i < 8;i++)
			{
				auto pos = ptrEffect[i]->GetComponent<Transform>()->GetPosition();
				m_forward[i] = 45 * i;
				pos.x += cos(m_forward[i] * XM_PI / 180) * m_speed;
				pos.y -= sin(m_forward[i] * XM_PI / 180) * m_speed;
				ptrEffect[i]->GetComponent<Transform>()->SetPosition(pos);

				// 開始時のポジションからm_removeDistanceより離れたら
				if ((m_startPos - pos).length() > m_removeDistance)
				{
					for (int j = 0;j < 8;j++)
					{
						GetStage()->RemoveGameObject<DeathEffectImg>(ptrEffect[j]);
					}
					m_ptrPlayerF = dynamic_pointer_cast<Player>(m_owner);
					m_ptrPlayerS = dynamic_pointer_cast<Player2>(m_owner);

					// この関数を呼んだのがプレイヤー１だったら
					if (m_ptrPlayerF)
					{
						m_ptrPlayerF->PlayerDeath();
					}
					// この関数を呼んだのがのがプレイヤー２だったら
					else if (m_ptrPlayerS)
					{
						m_ptrPlayerS->PlayerDeath();
					}
					GetStage()->RemoveGameObject<DeathEffect>(GetThis<DeathEffect>());
				}
			}
		}
	}
}
//end basecross
