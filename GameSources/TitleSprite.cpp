/* !
@file TitleSprite.h
@brief タイトルシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	TitleSprite::TitleSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// デストラクタ
	TitleSprite::~TitleSprite() {}

	// 初期化
	void TitleSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"TITLE");
	}

	// 更新処理
	void TitleSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}