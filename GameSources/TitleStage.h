/*!
@file TiteleStage.h
@brief タイトル画面
*/

#pragma once
#include "stdafx.h"
#include "ShutterSprite.h"

namespace basecross {
	class TitleStage : public Stage {
		
		bool stage = false;

		shared_ptr<SoundItem> m_bgm; // サウンドアイテム

		void CreateViewLight();//ビューの作成
		void CreateTitleSprite();//スプライトの作成
		//void PlayBGM();//BGMの作成
		shared_ptr<ShutterSprite> m_sFade;
		shared_ptr<ShutterSprite> m_nFade;
		shared_ptr<Sprites> m_ptrSprite; // フェード用スプライトのポインタ
		shared_ptr<PCTSpriteDraw> m_ptrSpriteDraw; // フェード用スプライトのドローコンポーネント

		float m_CurrentTime = 0.0f; // 経過時間
		float m_ToMovieTime = 10.0f; // ムービーステージまでの遷移時間
		float m_FadeTime = 1.0f; // フェードにかける時間
		Col4 m_diffuseColor; // フェード用スプライトの色設定用
		bool isFadeOut = false; // フェードアウトするかどうかのフラグ

	public:
		TitleStage() :
			Stage(),
			m_diffuseColor(1.0f, 1.0f, 1.0f, 0.0f) // フェード用スプライトは生成時に透明
		{
		}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		
	};
}