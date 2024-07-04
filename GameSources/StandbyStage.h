/*!
@file StandbyStage.h
@brief スタンバイステージ
@author 佐藤悠
@detail　待機画面の実装
*/

#pragma once
#include "stdafx.h"
#include "ShutterSprite.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		//時間
		float m_time = 2.0f;
		float m_Totaltime = 0.0f;
		//フェード
		shared_ptr<ShutterSprite> m_sFade;
		shared_ptr<ShutterSprite> m_nFade;
		//音楽
		shared_ptr<SoundItem> m_bgm;
		shared_ptr<SoundItem> m_kadouonn;
		//プレイヤー
		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;
		//ボタンスプライト
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite;
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite2;
		//磁石
		std::shared_ptr<MagnetS> m_ptrMagObjS;
		std::shared_ptr<MagnetN> m_ptrMagObjN;

		//準備完了
		bool playerReady = false;
		bool player2Ready = false;
		bool playerPositionFixed = false;
		bool player2PositionFixed = false;
		bool stage = false;
		bool OperationSEPlay = false;

		const WORD BUTTON_START = XINPUT_GAMEPAD_START;//スタートボタン
		const WORD BUTTON_BACK = XINPUT_GAMEPAD_BACK;//バックボタン

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		StandbyStage() :Stage(){}
		
		virtual ~StandbyStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

	};


}
//end basecross
