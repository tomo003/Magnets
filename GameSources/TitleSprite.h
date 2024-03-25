/* !
@file TitleSprite.h
@brief タイトルシーンの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TitleSprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		TitleSprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~TitleSprite();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理

	};
}