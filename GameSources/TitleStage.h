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

	public:
		TitleStage() :
			Stage()
		{
		}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		//virtual void OnDestroy()override;

		
	};
}