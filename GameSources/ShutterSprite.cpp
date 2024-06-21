/* !
@file ShutterSprite.cpp
@brief タイトルシーンからスタンバイシーンに移行する時のシャッター実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	ShutterSprite::ShutterSprite(const shared_ptr<Stage>& stage, Vec3& Pos, wstring TextureKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth() / 2, (float)App::GetApp()->GetGameHeight())),
		m_Pos(Pos),
		m_textureKey(TextureKey)
	{
	}
	// デストラクタ
	ShutterSprite::~ShutterSprite() {}

	
}