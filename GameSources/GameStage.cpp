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
		m_View = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<DuoCamera>();
		m_View->SetCamera(PtrCamera);
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
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(sound, XAUDIO2_LOOP_INFINITE, 0.8f);
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void GameStage::OnCreate() {
		try {
			m_ptrScene = App::GetApp()->GetScene<Scene>();
			m_ptrScene ->SetGameState(GameState::MainGame);
			m_ptrScene->SetPauseNum(0);
			m_ptrScene->SetResultNum(0);
			//ビューとライトの作成
			CreateViewLight();
			CreateObjGroup();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring strMap = DataDir + L"Maps\\";

			auto ptrCamera = dynamic_pointer_cast<DuoCamera>(m_View->GetCamera());

			switch (m_ptrScene->GetStageNum()) {
			case 1:
				CreateBackGround(L"BACKGROUND1");
				m_GameStageCsv.SetFileName(strMap + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_firstStageHeight);
				}

				break;
			case 2:
				CreateBackGround(L"BACKGROUND2");
				m_GameStageCsv.SetFileName(strMap + L"Stage2.csv");
				PlayBGM(L"GAMESTAGE2_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_secondStageHeight);
				}
				break;
			case 3:
				CreateBackGround(L"BACKGROUND3");
				m_GameStageCsv.SetFileName(strMap + L"Stage3.csv");
				PlayBGM(L"GAMESTAGE3_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_thirdStageHeight);
				}
				break;
			case 4:
				CreateBackGround(L"BACKGROUND4");
				m_GameStageCsv.SetFileName(strMap + L"Stage4.csv");
				PlayBGM(L"GAMESTAGE4_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_fourthStageHeight);
				}
				break;
			case 5:
				CreateBackGround(L"BACKGROUND5");
				m_GameStageCsv.SetFileName(strMap + L"Stage5.csv");
				PlayBGM(L"GAMESTAGE5_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_fifthStageHeight);
				}
				break;
			case 6:
				CreateBackGround(L"BACKGROUND6");
				m_GameStageCsv.SetFileName(strMap + L"Stage6.csv");
				PlayBGM(L"GAMESTAGE6_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_sixthStageHeight);
				}
				break;
			default:
				m_GameStageCsv.SetFileName(strMap + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				if (ptrCamera) {
					//カメラのステージごとの高さの設定
					ptrCamera->SetCameraHeight(m_firstStageHeight);
				}
				break;
			}
			m_GameStageCsv.ReadCsv();
			m_ptrScene->ResetScore(m_ptrScene->GetStageNum());

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
		auto stageNum = m_ptrScene->GetStageNum();
		for (int i = 0; i < 9; i++) {
			AddGameObject<BackGroundSprite2>(Vec3(50, 40, 1.0f), Vec3(-50 + (50 * i),0,0), texkey);
		}
	}

	//ステージクリア時に使用するUI（ステージセレクトに戻る、次のステージへ、タイトルに戻る）
	void GameStage::CreateAnimeSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-850.0f, -50.0f,0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);//ステージセレクトへ
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-300.0f, -50.0f, 0.0f), Vec2(650.0f, 500.0f), L"NEXTSTAGE", false);//次のステージへ
		m_SpVec[1] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(220.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);//タイトルに戻る
		m_SpVec[2] = PtrSp;
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
			m_key2->SetDrawActive(false);
			m_key3->SetDrawActive(false);
		}
		m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(-600.0f, 350.0f, 0.0f));
		m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(0.0f, 350.0f, 0.0f));
		m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(600.0f, 350.0f, 0.0f));
		m_resultScore = m_score;
		isGoal = true;
	}

	//最後のステージクリア時に使用するUI（ステージセレクトに戻る、タイトルに戻る）
	void GameStage::CreateAnimeSpriteLastStage() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-650.0f, -50.0f, 0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);//ステージセレクトへ
		PtrSp->SetSelect(true);
		m_SpVec2[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(20.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);//タイトルに戻る
		m_SpVec2[2] = PtrSp;
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
			m_key2->SetDrawActive(false);
			m_key3->SetDrawActive(false);
		}
		m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(-600.0f, 350.0f, 0.0f));
		m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(0.0f, 350.0f, 0.0f));
		m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(600.0f, 350.0f, 0.0f));
		m_resultScore = m_score;
		isGoal = true;
	}
	//クリア時の次のステージへとかの処理
	//コントローラー左スティックのの操作を取得して選択肢に応じたシーン移行を行う
	void GameStage::ClearResult() {
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			m_ptrScene = App::GetApp()->GetScene<Scene>();
			int ResultNum = m_ptrScene->GetResultNum();
			int StageNum = m_ptrScene->GetStageNum();
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
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						m_CntrolLock = true;
						m_ptrScene->SetResultNum(ResultNum);
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

	void GameStage::ClearResultLastStage() {
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			int ResultNum = m_ptrScene->GetResultNum();
			int StageNum = m_ptrScene->GetStageNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected) {
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLX >= 0.8) {
						ResultNum++;
						if (ResultNum > 2)
						{
							ResultNum = 0;
						}
						if (ResultNum == 1)
						{
							ResultNum = 2;
						}
						m_CntrolLock = true;
						m_Lock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenuLast(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						if (ResultNum == 1)
						{
							ResultNum = 0;
						}
						m_CntrolLock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenuLast(ResultNum);
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

	void GameStage::ChangeSelectMenuLast(int num) {
		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec2[i].lock();
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
					ptrGround = AddGameObject<Block>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0), L"GROUND_TX");
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

				case 3: //金属オブジェクト
					ptrMetal = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					MetalObjGroup->IntoGroup(ptrMetal);
					break;

				case 4: //左右に動く金属のオブジェクト
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), RIGHT_VEC, 3.5f);
					break;

				case 5: //上下に動く金属のオブジェクト
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
					ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(posX, float( - posY + m_CSVHeight - 0.47f), 0));
					SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
					break;

				case 9://ベルトコンベア右回り端
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5f));
					break;

				case 10://ベルトコンベア右回り真ん中
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5f));
					break;

				case 11://ベルトコンベア左回り端
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5f));
					break;

				case 12://ベルトコンベア左回り真ん中
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5f));
					break;

				case 13: //スタート
					ptrStart = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					SetSharedGameObject(L"Start", ptrStart);
					break;

				case 14: //セーブポイント
					ptrSavePoint = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1.0f, 0));
					SavePointGroup->IntoGroup(ptrSavePoint);
					break;

				case 15: //ゴール
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1.0f, 0));
					SetSharedGameObject(L"Goal", ptrGround);
					break;

				case 16: //歯車右回り
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_RIGHT, 60.0f, STATE_METAL, STATE_NONE);
					break;

				case 17: //歯車左回り
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_LEFT, 80.0f, STATE_NONE, STATE_METAL);
					break;

				case 18: //鍵
					AddGameObject<CoinObject>(Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 19: //磁力のないハンマー
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0),STATE_NONE);
					break;

				case 20: //2*2の地面オブジェクト
					ptrGround = AddGameObject<Block>(Vec3(2.0f,2.0f,1.0f) / size, Vec3(posX+0.5f, - posY + m_CSVHeight - 0.5f, 0), L"CONCRETE2_TX");
					break;

				case 21: //3*3の地面王ジェクト
					ptrGround = AddGameObject<Block>(Vec3(3.0f,3.0f,1.0f) / size, Vec3(posX+1.0f, -posY + m_CSVHeight-1.0f, 0),L"CONCRETE3_TX");
					break;

				case 22: //1Pが上に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight,0.5f), 1);
					break;

				case 23: //1Pが下に行くガイド
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5f), 2);
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

				case 28://S極のハンマー
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0), STATE_MAG_S);
					break;

				case 29://N極のハンマー
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0), STATE_MAG_N);
					break;

				default:
					break;
				}
			}
		}
	}

	void GameStage::CreateKeyLoad(const int scene, const Vec3 pos) {
		int score = App::GetApp()->GetScene<Scene>()->GetScore(scene);
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
		}
		if (m_key2 != NULL) {
			m_key2->SetDrawActive(false);
		}
		if (m_key3 != NULL) {
			m_key3->SetDrawActive(false);
		}
		switch (score) {
		case 0:
			m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 1:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 2:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		default:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		}
	}


	void GameStage::OnUpdate()
	{
		m_InputHandler.PushHandler(GetThis<GameStage>());
		int stageNum = m_ptrScene->GetStageNum();
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			if (stageNum != 6)
			{
				if (m_Clear <= false)
				{
					m_Clear = true;
					CreateAnimeSprite();
				}
				ClearResult();
			}
			else
			{
				if (m_Clear <= false)
				{
					m_Clear = true;
					CreateAnimeSpriteLastStage();
				}
				ClearResultLastStage();
			}
			
		}
		m_score = m_ptrScene->GetScore(m_ptrScene->GetStageNum());
		if (m_score > m_previousScore) {
			m_previousScore = m_score;
			CreateKeyLoad(m_ptrScene->GetStageNum(), Vec3(-740.0f, 400.0f, 0.0f));
		}
		if (m_ptrScene->GetGameState() == GameState::Pause)
		{
			Menu();
		}
		CollisionSwitch();

		if (isGoal) {
			m_time--;

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			auto pos = m_ptrPlayer1->GetComponent<Transform>()->GetPosition();
			
			if (m_resultScore >= 1) {
				if (!isScore1) {
					if (m_time <= 90.0f) {
						m_key1->SetDrawActive(false);
						m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(-600.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x , pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore1 = true;
					}
				}
			}
			if (m_resultScore >= 2) {
				if (m_time <= 50.0f) {
					if (!isScore2) {
						m_key2->SetDrawActive(false);
						m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(0.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x , pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore2 = true;
					}
				}
			}
			if (m_resultScore >= 3) {
				if (m_time <= 10.0f) {
					if (!isScore3) {
						m_key3->SetDrawActive(false);
						m_key3 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(600.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x + 5.0f, pos.y -2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						AddGameObject<EffectPlayer>(Vec3(pos.x - 5.0f, pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore3 = true;
					}
				}
			}
		}

		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];
		//Start・Backボタン同時押しでタイトルに戻る
		if (firstPad.wButtons & BUTTON_START && firstPad.wButtons & BUTTON_BACK ||
			secondPad.wButtons & BUTTON_START && secondPad.wButtons & BUTTON_BACK) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}
	void GameStage::OnPushSTART()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		if (m_ptrScene->GetGameState() == GameState::MainGame)
		{
			ptrPlayer->SetUpdateActive(false);
			ptrPlayer2->SetUpdateActive(false);
			m_ptrScene->SetGameState(GameState::Pause);

			CreatePauseSprite();
		}
		else if (m_ptrScene->GetGameState() == GameState::Pause)
	{
			ptrPlayer->SetUpdateActive(true);
			ptrPlayer2->SetUpdateActive(true);
			m_ptrScene->SetGameState(GameState::MainGame);
		}
	}
	//オプションボタンを押すとポーズして操作する機能
	void GameStage::Menu() {
		if (m_ptrScene->GetGameState() == GameState::Pause)
		{
			auto m_ptrScene = App::GetApp()->GetScene<Scene>();
			int	 PauseNum = m_ptrScene->GetPauseNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			if (CntlVec[0].bConnected) {
				m_ptrScene->ResetScore(m_ptrScene->GetStageNum());
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLY >= 0.8) {
						PauseNum--;
						if (PauseNum < 0)
						{
							PauseNum = 2;
						}
						m_CntrolLock = true;
						m_ptrScene->SetPauseNum(PauseNum);
						ChangeSelectPauseMenu(PauseNum);
					}
					else if (CntlVec[0].fThumbLY <= -0.8f) {
						PauseNum++;
						if (PauseNum > 2) {
							PauseNum = 0;
						}
						m_CntrolLock = true;
						m_ptrScene->SetPauseNum(PauseNum);
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

	//ポーズメニューで使用するスプライト処理
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
		if (!m_pushButton)
		{
			if (ptrPlayer->IsGoal() && ptrPlayer2->IsGoal()) {
				if (m_ptrScene->GetGameState() == GameState::GameClear)
				{
					m_pushButton = true;
					AddGameObject<FadeOut>(L"FADE_WHITE");
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);

					int ResultNum = m_ptrScene->GetResultNum();
					m_Lock = true;
					m_CntrolLock = true;
					int StageNum = m_ptrScene->GetStageNum();

					if (ResultNum == 0)
					{
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
					}
					if (ResultNum == 1)
					{
						StageNum++;

						int m_score = 0;
						for (int i = 1; i < 7; i++) {
							m_score += m_ptrScene->GetScore(i);
						}
						if (StageNum <= 3) {
							m_ptrScene->SetStageNum(StageNum);
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						if (StageNum == 4) {
							if (m_score >= 7) {
								m_ptrScene->SetStageNum(StageNum);
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
							}
							else {
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
							}
						}
						if (StageNum == 5) {
							if (m_score >= 10) {
								m_ptrScene->SetStageNum(StageNum);
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
							}
							else {
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
							}
						}
						if (StageNum == 6) {
							if (m_score >= 13) {
								m_ptrScene->SetStageNum(StageNum);
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
			if (m_ptrScene->GetGameState() == GameState::Pause)
			{
				m_pushButton = true;
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				AddGameObject<FadeOut>(L"FADE_WHITE");
				int	 PauseNum = m_ptrScene->GetPauseNum();
				m_pushButton = true;
				m_CntrolLock = true;

				//m_ptrScene->SetGameState(GameState::IsSelect);

				if (PauseNum == 0)
				{
					m_ptrScene->ResetScore(m_ptrScene->GetStageNum());
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
				}
				if (PauseNum == 1)
				{
					m_ptrScene->ResetScore(m_ptrScene->GetStageNum());
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

				}
				if (PauseNum == 2)
				{
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
				}
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
