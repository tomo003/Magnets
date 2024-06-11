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

		//スプライトWeak_ptrの配列
		vector<weak_ptr<FlashSprite>> m_SpVec;
		std::shared_ptr<FlashSprite> m_Flash;
		vector<weak_ptr<FlashSprite>> m_PsVec;

		//ビューの作成
		void CreateViewLight();

		void CreateCsvObjects();

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
	};


}
//end basecross

