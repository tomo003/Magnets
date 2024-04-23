/* !
@file FadeIn.cpp
@brief フェードインの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	FadeIn::FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight())),
		m_texKey(texKey)
	{
	}
	// デストラクタ
	FadeIn::~FadeIn() {}
	// ここまで

	// 初期化
	void FadeIn::OnCreate()
	{
		// 初期値の設定(縦、高さ、横)
		Sprites::CreateFadeSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, m_texKey, FadeType::FadeIn);
	}

	// 更新処理
	void FadeIn::OnUpdate()
	{
		Sprites::UpdateFadeSprite(1.0f);
	}
}