/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<DuoCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateObjGroup() {
		CreateSharedObjectGroup(L"BeltConveyorLeft");
		CreateSharedObjectGroup(L"BeltConveyorRight");
		CreateSharedObjectGroup(L"BeltConveyorSideLeft");
		CreateSharedObjectGroup(L"BeltConveyorSideRight");
	}

	void GameStage::PlayBGM(wstring sound) {
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(sound, XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void GameStage::OnCreate() {
		try {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene ->SetGameState(GameState::MainGame);
			PtrScene->SetPauseNum(0);
			PtrScene->SetResultNum(0);
			//ビューとライトの作成
			CreateViewLight();
			CreateObjGroup();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			switch (PtrScene->GetStageNum()) {
			case 1:
				CreateBackGround(L"BACKGROUND1");
				m_GameStageCsv.SetFileName(DataDir + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				break;
			case 2:
				CreateBackGround(L"BACKGROUND2");
				m_GameStageCsv.SetFileName(DataDir + L"Stage2.csv");
				PlayBGM(L"GAMESTAGE2_BGM");
				break;
			case 3:
				CreateBackGround(L"BACKGROUND3");
				m_GameStageCsv.SetFileName(DataDir + L"Stage3.csv");
				PlayBGM(L"GAMESTAGE3_BGM");
				break;
			case 4:
				CreateBackGround(L"BACKGROUND4");
				m_GameStageCsv.SetFileName(DataDir + L"Stage4.csv");
				PlayBGM(L"GAMESTAGE4_BGM");
				break;
			case 5:
				CreateBackGround(L"BACKGROUND5");
				m_GameStageCsv.SetFileName(DataDir + L"Stage5.csv");
				PlayBGM(L"GAMESTAGE5_BGM");
				break;
			case 6:
				CreateBackGround(L"BACKGROUND6");
				m_GameStageCsv.SetFileName(DataDir + L"Stage6.csv");
				PlayBGM(L"GAMESTAGE6_BGM");
				break;
			default:
				m_GameStageCsv.SetFileName(DataDir + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				break;
			}
			m_GameStageCsv.ReadCsv();
			PtrScene->ResetScore(PtrScene->GetStageNum());

			// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//プレイヤーオブジェクトを追加
			m_ptrPlayer1 = AddGameObject<Player>();
			SetSharedGameObject(L"Player", m_ptrPlayer1);
			m_ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", m_ptrPlayer2);

			CreateCsvObjects();

			AddGameObject<StartMoveObject>(Vec3(1.0f), Vec3(1.0f));

			// 磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			//AddGameObject<MoveMetalObject>(Vec3(30, 5, 0));


		}
		catch (...) {
			throw;
		}
	}

	/**
	* @brief 背景生成関数
	* @param[in] texkey(背景テクスチャの名前)
	* @return 戻り値なし
	* @details forループで複数の背景を表示させる
	*/
	void GameStage::CreateBackGround(const wstring& texkey) {
		for (int i = 0; i <= 5; i++) {
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(-50 + (40 * i),0,0), texkey);
		}
	}

	void GameStage::CreateAnimeSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-850.0f, -50.0f,0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-300.0f, -50.0f, 0.0f), Vec2(650.0f, 500.0f), L"NEXTSTAGE", false);
		m_SpVec[1] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(220.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);
		m_SpVec[2] = PtrSp;
	}

	void GameStage::ClearResult() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::GameClear)
		{
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int ResultNum = PtrScene->GetResultNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			if (CntlVec[0].bConnected) {
				
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLX >= 0.8) {
						ResultNum++;
						if (ResultNum > 2)
						{
							ResultNum = 0;
						}
						m_CntrolLock = true;
						m_Lock = true;
						PtrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						m_CntrolLock = true;
						PtrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
				}
				else {
					if (CntlVec[0].fThumbLX == 0.0f && !m_pushButton) {
						m_CntrolLock = false;
					}
				}
			}
		}
	}

	void GameStage::ChangeSelectMenu(int num) {
		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if (i == num) {
					shptr->SetSelect(true);
				}
				else { 
					shptr->SetSelect(false);
				}
			}
		}
	}

	void GameStage::CreateCsvObjects() {
		auto SavePointGroup = CreateSharedObjectGroup(L"SavePoint"); // セーブポイントグループ
		auto GroundObjGroup = CreateSharedObjectGroup(L"Ground"); // 床オブジェクトグループ
		auto MagAreaGroup = CreateSharedObjectGroup(L"MagnetAreas"); // マグネットエリアグループ
		auto NMagObjGroup = CreateSharedObjectGroup(L"NMagnets"); // Nマグネットグループ
		auto SMagObjGroup = CreateSharedObjectGroup(L"SMagnets"); // Sマグネットグループ
		auto MetalObjGroup = CreateSharedObjectGroup(L"MetalObj"); // 金属オブジェクト(不動)グループ

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;
		std::shared_ptr<GameObject> ptrMetal;
		std::shared_ptr<GameObject> ptrMoveMetal;
		std::shared_ptr<GameObject> ptrStart;
		std::shared_ptr<GameObject> ptrSavePoint;
		std::shared_ptr<GameObject> ptrGoal;
		std::shared_ptr<GameObject> ptrMoveFloor;
		std::shared_ptr<GameObject> ptrMoveFloorButton;

		auto& LineVec = m_GameStageCsv.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				float posX = (float)((int)j -5) / size;
				float posY = (float)((int)i) / size;
				int TokensNum = stoi(Tokens[j]);


				switch (TokensNum) {
				case 0: //通常地面
					ptrGround = AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					GroundObjGroup->IntoGroup(ptrGround);
					break;

				case 1: //磁石N極
					ptrMag = AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					NMagObjGroup->IntoGroup(ptrMag);
					break;

				case 2: //磁石S極
					ptrMag = AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					SMagObjGroup->IntoGroup(ptrMag);
					break;

				case 3: //金属
					ptrMetal = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					MetalObjGroup->IntoGroup(ptrMetal);
					break;

				case 4: //金属動くやつ
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), RIGHT_VEC, 3.5f);
					break;

				case 5: //金属動くやつ
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), UP_VEC, 3.5f);
					break;

				case 6://壊せる壁
					AddGameObject<BreakWall>(Vec3(posX, -posY + m_CSVHeight, 0), Vec3(0.0f));
					break;

				case 7://ボタン押したら動く床
					ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(8.2f, 0.9f, 0.9f), Vec3(posX + 5.0f, -posY + m_CSVHeight, 0), LEFT_VEC);
					SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
					break;

				case 8://動く床発動用ボタン
					ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(posX, -posY + m_CSVHeight - 0.47, 0));
					SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
					break;

				case 9://ベルトコンベア右回り端
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 10://ベルトコンベア右回り真ん中
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 11://ベルトコンベア左回り端
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 12://ベルトコンベア左回り真ん中
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 13: //スタート
					ptrStart = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					SetSharedGameObject(L"Start", ptrStart);
					break;

				case 14: //セーブポイント
					ptrSavePoint = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1, 0));
					SavePointGroup->IntoGroup(ptrSavePoint);
					break;

				case 15: //ゴール
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1, 0));
					SetSharedGameObject(L"Goal", ptrGround);
					break;

				case 16: //歯車右回り
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_RIGHT, 50.0f, STATE_METAL, STATE_NONE);
					break;

				case 17: //歯車左回り
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_LEFT, 60.0f, STATE_NONE, STATE_METAL);
					break;

				case 18: //鍵
					AddGameObject<CoinObject>(Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 20: //2*2の地面オブジェクト
					ptrGround = AddGameObject<ChangeTextureBox>(Vec3(2.0f,2.0f,1.0f) / size, Vec3(posX+0.5, -posY + m_CSVHeight-0.5, 0),L"CONCRETE2_TX");
					break;

				case 21: //3*3の地面王ジェクト
					ptrGround = AddGameObject<ChangeTextureBox>(Vec3(3.0f,3.0f,1.0f) / size, Vec3(posX+1, -posY + m_CSVHeight-1, 0),L"CONCRETE3_TX");
					break;

				case 22: //1Pが上に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight,0.5), 1);
					break;

				case 23: //1Pが下に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 2);
					break;

				case 24: //1Pが真っすぐに行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 3);
					break;

				case 25: //2Pが上に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 4);
					break;

				case 26: //2Pが下に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 5);
					break;

				case 27: //2Pが真っすぐに行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 6);
					break;

				default:
					break;
				}
			}
		}
	}

	void GameStage::CreateKeyLoad(const int scene, const Vec3 pos) {
		int score = App::GetApp()->GetScene<Scene>()->GetScore(scene);
		switch (score) {
		case 0:
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 1:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 2:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		default:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		}
	}


	void GameStage::OnUpdate()
	{
		m_InputHandler.PushHandler(GetThis<GameStage>());
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::GameClear)
		{
			if (m_Clear <= false)
			{
				m_Clear = true;
				CreateAnimeSprite();
			}
			ClearResult();
		}
		m_score = PtrScene->GetScore(PtrScene->GetStageNum());
		if (m_score > m_previousScore) {
			m_previousScore = m_score;
			CreateKeyLoad(PtrScene->GetStageNum(), Vec3(-740.0f, 400.0f, 0.0f));
		}
		if (PtrScene->GetGameState() == GameState::Pause)
		{
			Menu();
		}
		CollisionSwitch();
	}
	void GameStage::OnPushSTART()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::MainGame)
		{
			ptrPlayer->SetUpdateActive(false);
			ptrPlayer2->SetUpdateActive(false);
			PtrScene->SetGameState(GameState::Pause);

			CreatePauseSprite();
		}
		else if (PtrScene->GetGameState() == GameState::Pause)
	{
			ptrPlayer->SetUpdateActive(true);
			ptrPlayer2->SetUpdateActive(true);
			PtrScene->SetGameState(GameState::MainGame);
		}
	}
	void GameStage::Menu() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::Pause)
		{
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int	 PauseNum = PtrScene->GetPauseNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			if (CntlVec[0].bConnected) {
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLY >= 0.8) {
						PauseNum--;
						if (PauseNum < 0)
						{
							PauseNum = 2;
						}
						m_CntrolLock = true;
						PtrScene->SetPauseNum(PauseNum);
						ChangeSelectPauseMenu(PauseNum);
					}
					else if (CntlVec[0].fThumbLY <= -0.8f) {
						PauseNum++;
						if (PauseNum > 2) {
							PauseNum = 0;
						}
						m_CntrolLock = true;
						PtrScene->SetPauseNum(PauseNum);
						ChangeSelectPauseMenu(PauseNum);
					}
				}
				else {
					if (CntlVec[0].fThumbLY == 0.0f && !m_pushButton) {
						m_CntrolLock = false;
					}
				}
			}
		}
	}

	void GameStage::CreatePauseSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,500.0f,0.0f), Vec2(800.0f, 750.0f), L"BACKTOSTAGESELECT", false);
		m_SpVec[0] = PtrSp;
		PtrSp->SetSelect(true);
		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,300.0f,0.0f), Vec2(800.0f, 750.0f), L"RETRY", false);
		m_SpVec[1] = PtrSp;
		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,70.0f,0.0f), Vec2(800.0f, 750.0f), L"BACKTOTITLE", false);
		m_SpVec[2] = PtrSp;
		AddGameObject<PauseSprite>(L"PAUSE_BACK", true, Vec2(700.0f, 750.0f), Vec3(0.0f),Col4(1.0f),true);
		AddGameObject<PauseSprite>(L"MENU", true, Vec2(700.0f, 500.0f), Vec3(0.0f, 300.0f, 0.0f), Col4(1.0f), true);
	}

	void GameStage::ChangeSelectPauseMenu(int num) {

		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if ((i) == num) {
					shptr->SetSelect(true);
				}
				else {
					shptr->SetSelect(false);
				}
			}
		}
	}

	void GameStage::OnPushB()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		if (ptrPlayer->IsGoal() && ptrPlayer2->IsGoal()) {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			if (PtrScene->GetGameState() == GameState::GameClear)
				AddGameObject<FadeOut>(L"FADE_WHITE");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
			{
				m_pushButton = true;
				int ResultNum = PtrScene->GetResultNum();
				m_Lock = true;
				m_CntrolLock = true;
				int StageNum = PtrScene->GetStageNum();

				if (ResultNum == 0)
				{
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
				}
				if (ResultNum == 1)
				{
					StageNum++;

					int m_score = 0;
					for (int i = 1; i < 7; i++) {
						m_score += PtrScene->GetScore(i);
					}
					if (StageNum <= 3) {
						PtrScene->SetStageNum(StageNum);
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					}
					if (StageNum == 4) {
						if (m_score >= 7) {
							PtrScene->SetStageNum(StageNum);
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						else {
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
						}
					}
					if (StageNum == 5) {
						if (m_score >= 10) {
							PtrScene->SetStageNum(StageNum);
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						else {
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
						}
					}
					if (StageNum == 6) {
						if (m_score >= 13) {
							PtrScene->SetStageNum(StageNum);
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						else {
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
						}
					}
					if (StageNum > 6) {
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
					}
				}

				if (ResultNum == 2)
				{
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
				}

			}
		}
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::Pause)
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
			AddGameObject<FadeOut>(L"FADE_WHITE");
			int	 PauseNum = PtrScene->GetPauseNum();
			m_pushButton = true;
			m_CntrolLock = true;

			//PtrScene->SetGameState(GameState::IsSelect);

			if (PauseNum == 0)
			{
				PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
			}
			if (PauseNum == 1)
			{
				PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

			}
			if (PauseNum == 2)
			{
				PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}

	}

	void GameStage::CollisionSwitch() {
		GroupCollisionSwitch(L"Ground");
	}

	void GameStage::GroupCollisionSwitch(wstring groupStr) {
		Vec3 player1Pos = m_ptrPlayer1->GetComponent<Transform>()->GetWorldPosition();
		Vec3 player2Pos = m_ptrPlayer2->GetComponent<Transform>()->GetWorldPosition();

		auto ptrGroup = GetSharedObjectGroup(groupStr);
		auto& GroupVec = ptrGroup->GetGroupVector();
		for (auto& v : GroupVec) {
			auto shObj = v.lock();
			if (shObj) {
				auto shGround = dynamic_pointer_cast<GameObject>(shObj);
				if (shGround) {
					auto shGroundPos = shGround->GetComponent<Transform>()->GetWorldPosition();
					auto shaGroundColl = shGround->GetComponent<CollisionObb>();
					if (length(player1Pos - shGroundPos) <= 1.5f) {
						//shaGroundColl->SetDrawActive(true);
						shaGroundColl->SetUpdateActive(true);
					}
					else if (shaGroundColl->IsUpdateActive()) {
						//shaGroundColl->SetDrawActive(false);
						shaGroundColl->SetUpdateActive(false);
					}

					if (length(player2Pos - shGroundPos) <= 1.5f) {
						//shaGroundColl->SetDrawActive(true);
						shaGroundColl->SetUpdateActive(true);
					}
				}
			}
		}
	}

}
//end basecross
