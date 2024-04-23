/*!
@file FadeIn.h
@brief フェードインの定義
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeIn : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

		wstring m_texKey; // テクスチャ名

	public:
		// コンストラクタ
		FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey);
		// デストラクタ
		~FadeIn();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
	};
}
