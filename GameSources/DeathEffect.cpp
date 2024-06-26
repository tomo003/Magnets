/*!
@file DeathEffect.cpp
@brief 死亡時のエフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	DeathEffectImg::DeathEffectImg(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	DeathEffectImg::~DeathEffectImg() {}

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
		auto ownerTrans = m_owner->GetComponent<Transform>();

		for (int i = 0; i < 8;i++)
		{
			ptrEffect[i] = GetStage()->AddGameObject<DeathEffectImg>(Vec3(1.0f), ownerTrans->GetWorldPosition());
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
		if (m_time > 0)
		{
			for (int i = 0;i < 8;i++)
			{
				auto pos = ptrEffect[i]->GetComponent<Transform>()->GetWorldPosition();
				m_forward[i] = 45 * i;
				pos.x += cos(m_forward[i] * XM_PI / 180) * m_speed;
				pos.y -= sin(m_forward[i] * XM_PI / 180) * m_speed;
				ptrEffect[i]->GetComponent<Transform>()->SetWorldPosition(pos);
				if (pos.length() > m_removeDistance)
				{
					for (int j = 0;j < 8;j++)
					{
						GetStage()->RemoveGameObject<DeathEffectImg>(ptrEffect[j]);
					}
				}
			}
		}
	}
}
//end basecross
