/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include"FlashSprite.h"
namespace basecross {
	class FlashSprite;

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;

		InputHandler<GameStage> m_InputHandler;

		shared_ptr<SoundItem> m_bgm;


		bool isCreateMaagnets = true;

		//ビューの作成
		void CreateViewLight();

		void CreateCsvObjects();

		float m_CSVHight = +42;

		vector<weak_ptr<FlashSprite>> m_SpVec;

		bool m_CntrolLock;

		void ChangeSelectMenu(int num);

		bool m_Clear;
		bool m_pushButton;
		bool m_Lock = false;
	public:


		//構築と破棄
		GameStage() :Stage(),m_CntrolLock(false), m_SpVec(3) {}
		virtual ~GameStage() {}


		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM();
		void CreateAnimeSprite();
		void ClearResult();

		void OnPushB();
	};


}
//end basecross

