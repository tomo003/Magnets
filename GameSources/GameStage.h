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
	class GameStage : public Stage {

	private:
		CsvFile m_GameStageCsv;

		shared_ptr<SoundItem> m_bgm;

		bool isCreateMaagnets = true;

		//ビューの作成
		void CreateViewLight();

		void CreateCsvObjects();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM();
	};


}
//end basecross

