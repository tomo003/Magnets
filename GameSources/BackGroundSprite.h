/* !
@file BackGroundSprite.h
@brief ゲームステージの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class BackGroundSprite : public GameObject {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		BackGroundSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; // 初期化
	};

	class BackGroundSprite2 : public GameObject {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		BackGroundSprite2(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; // 初期化
	};
}