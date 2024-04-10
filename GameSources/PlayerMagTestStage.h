/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class PlayerMagTestStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		PlayerMagTestStage() :Stage() {}
		virtual ~PlayerMagTestStage() {}
		//初期化
		virtual void OnCreate()override;

		void CreateObjGroup();
	};


}
//end basecross

