/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include"FlashSprite.h"
#include "StageSelectSprite.h"

namespace basecross {
	class FlashSprite;

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<SingleView> m_View;

		CsvFile m_GameStageCsv;

		InputHandler<GameStage> m_InputHandler;

		shared_ptr<SoundItem> m_bgm;

		bool isCreateMaagnets = true;

		//スプライトWeak_ptrの配列
		vector<weak_ptr<FlashSprite>> m_SpVec;
		std::shared_ptr<FlashSprite> m_Flash;
		vector<weak_ptr<FlashSprite>> m_PsVec;

		std::shared_ptr<SelectSprite> m_key1;
		std::shared_ptr<SelectSprite> m_key2;
		std::shared_ptr<SelectSprite> m_key3;
		bool isGoal = false;
		float m_time = 100;
		int m_resultScore = 0;

		//ビューの作成
		void CreateViewLight();

		void CreateCsvObjects();

		//ステージごとのカメラの高さ設定
		float m_firstStageHeight = 0;  //ステージ1
		float m_secondStageHeight = 0; //ステージ2
		float m_thirdStageHeight = 0;  //ステージ3
		float m_fourthStageHeight = 2; //ステージ4
		float m_fifthStageHeight = 2;  //ステージ5
		float m_sixthStageHeight = 0;  //ステージ6

		float m_CSVHeight = +42;

		int m_score = 0;
		int m_previousScore = -1;

		bool m_CntrolLock;

		void Menu();
		void ChangeSelectMenu(int num);
		void ChangeSelectPauseMenu(int num);


		bool m_Clear;
		bool m_pushButton;
		bool m_Lock = false;

		shared_ptr<GameObject> m_ptrPlayer1;
		shared_ptr<GameObject> m_ptrPlayer2;

	public:


		//構築と破棄
		GameStage() :Stage(),m_CntrolLock(false), m_SpVec(3),m_PsVec(3) {}
		virtual ~GameStage() {}


		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM(wstring sound);
		void CreateAnimeSprite();
		void ClearResult();
		void CreateKeyLoad(const int scene, const Vec3 pos);

		/**
		* @brief 背景生成関数
		* @param[in] texkey(背景テクスチャの名前)
		* @return 戻り値なし
		* @details forループで複数の背景を表示させる
		*/
		void CreateBackGround(const wstring& texkey);
		void CreatePauseSprite();
		void OnPushSTART();
		void OnPushB();

		/*!
		@brief コリジョンをON/OFFする関数
		@param 引数なし
		@return 戻り値なし
		*/
		void CollisionSwitch();

		/*!
		@brief コリジョンをON/OFFする関数(グループ)
		@param wstring groupStr グループ名
		@return 戻り値なし
		*/
		void GroupCollisionSwitch(wstring groupStr);
	};

}
//end basecross

