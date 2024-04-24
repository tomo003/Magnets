/*!
@file StandbyStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		//enum class EState {
		//	eFalse = -1, // 無
		//	eN = 1, // Ｎ極
		//	eS = 2 // Ｓ極
		//};
		float m_time = 2.0f;

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
		bool playerBPush = false;
		bool player2BPush = false;
		bool playerReady = false;
		bool player2Ready = false;
		bool stage = false;
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		StandbyStage() :Stage(){}
		
		virtual ~StandbyStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void CreateObjGroup();
	};


}
//end basecross
