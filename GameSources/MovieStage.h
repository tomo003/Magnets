/*!
@file MovieStage.h
@brief タイトルムービーを流す

*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	class TitleMovieStage : public MovieStage {
		//入力ハンドラー
		InputHandler2<TitleMovieStage> m_InputHandler;

		shared_ptr<Sprites> m_ptrSprite; // フェード用スプライトのポインタ
		shared_ptr<PCTSpriteDraw> m_ptrSpriteDraw; // フェード用スプライトのドローコンポーネント

		float m_FadeTime = 1.0f; // フェードアウトにかける時間
		Col4 m_diffuseColor; // フェードスプライトの色保持用
		bool isFadeOut = false; // フェードアウトするかどうかのフラグ

	public:
		//構築と破棄
		TitleMovieStage() :
			MovieStage(),
			m_diffuseColor(1.0f, 1.0f, 1.0f, 0.0f)
		{
		}
		virtual ~TitleMovieStage() {}
		//初期化
		void CreateViewLight();
		void OnCreate()override;
		void OnUpdate() override;
		//ボタン
		void OnPushAny();
		//void OnReset();
	};


}
//end basecross
