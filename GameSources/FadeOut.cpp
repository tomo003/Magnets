/* !
@file FadeOut.cpp
@brief フェードアウトの実装
@prod 芳賀 祐紀
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	FadeOut::FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight())),
		m_texKey(texKey)
	{
	}
	// デストラクタ
	FadeOut::~FadeOut() {}
	// ここまで

	// 初期化
	void FadeOut::OnCreate()
	{
		// 初期値の設定(縦、高さ、横)
		Sprites::CreateFadeSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, m_texKey, FadeType::FadeOut);
	}

	// 更新処理
	void FadeOut::OnUpdate()
	{
		Sprites::UpdateFadeSprite(1.0f);
	}
}