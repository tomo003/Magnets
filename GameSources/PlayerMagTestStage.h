/*!
@file PlayerMagTestStage.h
@brief プレイヤーの機能やオブジェクトのテストステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class PlayerMagTestStage : public Stage {
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3
		};

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		PlayerMagTestStage() :Stage() {}
		virtual ~PlayerMagTestStage() {}
		//初期化
		virtual void OnCreate()override;

		void CreateObjGroup();

		/**
		* @brief 背景生成関数
		* @param[in] texkey(背景テクスチャの名前)
		* @return 戻り値なし
		* @details forループで複数の背景を表示させる
		*/
		void CreateBackGround(const wstring& texkey);
	};


}
//end basecross

