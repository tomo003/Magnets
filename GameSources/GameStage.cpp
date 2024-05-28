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

	void GameStage::PlayBGM() {
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"GAMESTAGE_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void GameStage::OnCreate() {
		try {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			//ビューとライトの作成
			CreateViewLight();
			CreateObjGroup();
			PlayBGM();
			//背景
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(-50,0,0), L"BACKGROUND1");
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(-10,0,0), L"BACKGROUND2");
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(30,0,0), L"BACKGROUND3");
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(70,0,0), L"BACKGROUND4");
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(100,0,0), L"BACKGROUND5");

			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(3.0f, 4.0f, 0.0f));

			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-3.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-2.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, 2.0f, 0.0f));

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			switch (PtrScene->GetStageNum()) {
			case 1:
				m_GameStageCsv.SetFileName(DataDir + L"Stage1.csv");
				break;
			case 2:
				m_GameStageCsv.SetFileName(DataDir + L"Stage2.csv");
				break;
			case 3:
				m_GameStageCsv.SetFileName(DataDir + L"MagTest01.csv");
				break;
			case 4:
				m_GameStageCsv.SetFileName(DataDir + L"GameStage4.csv");
				break;
			case 5:
				m_GameStageCsv.SetFileName(DataDir + L"GameStage5.csv");
				break;
			case 6:
				m_GameStageCsv.SetFileName(DataDir + L"GameStage6.csv");
				break;
			default:
				m_GameStageCsv.SetFileName(DataDir + L"GameStage1.csv");
				break;
			}
			m_GameStageCsv.ReadCsv();


			// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//プレイヤーオブジェクトを追加
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

			CreateCsvObjects();

			// 磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			//AddGameObject<MoveMetalObject>(Vec3(30, 5, 0));


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateCsvObjects() {
		auto SavePointGroup = CreateSharedObjectGroup(L"SavePoint");

		std::shared_ptr<GameObject> ptrMoveMetal;

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;
		std::shared_ptr<GameObject> ptrStart;
		std::shared_ptr<GameObject> ptrSavePoint;
		std::shared_ptr<GameObject> ptrGoalSquareRed;
		std::shared_ptr<GameObject> ptrGoalSquareBlue;
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
					ptrGround = AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					isCreateMaagnets = false;
					break;

				case 1: //磁石N極
					AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					break;

				case 2: //磁石S極
					AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					break;

				case 3: //金属
					ptrMoveMetal = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					break;

				case 4: //金属動くやつ
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHight, 0));
					break;

				case 7://ボタン押したら動く床
					ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(7.5f, 0.9f, 0.9f), Vec3(posX + 4.7, -posY + m_CSVHight , 0),  Vec3(-1.0f, 0.0f, 0.0f));
					SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
					break;

				case 8://動く床発動用ボタン
					ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(posX, -posY + m_CSVHight-0.48, 0));
					SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
					break;

				case 9://ベルトコンベア右回り端
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, -0.5));
					break;

				case 10://ベルトコンベア右回り真ん中
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, -0.5));
					break;

				case 11://ベルトコンベア左回り端
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, -0.5));
					break;

				case 12://ベルトコンベア左回り真ん中
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, -0.5));
					break;

				case 13: //スタート
					ptrStart = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight, 0));
					SetSharedGameObject(L"Start", ptrStart);
					break;

				case 14: //セーブポイント
					ptrSavePoint = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight + 1, 0));
					SavePointGroup->IntoGroup(ptrSavePoint);
					isCreateMaagnets = false;
					break;

				case 15: //ゴール
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight + 1, 0));
					ptrGoalSquareRed = AddGameObject<GoalSquareRed>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight + 7, 0));
					SetSharedGameObject(L"GoalSquareRed", ptrGoalSquareRed);
					ptrGoalSquareBlue = AddGameObject<GoalSquareBlue>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHight + 9, 0));
					SetSharedGameObject(L"GoalSquareBlue", ptrGoalSquareBlue);
					isCreateMaagnets = false;
					break;

				default:
					break;
				}
			}
		}
	}

}
//end basecross
