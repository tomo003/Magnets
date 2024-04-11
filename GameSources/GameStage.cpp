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
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
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

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateObjGroup();

			AddGameObject<BackGroundSprite>();

			AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 4.0f, 0.0f));
			AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 4.0f, 0.0f));
			AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(3.0f, 4.0f, 0.0f));

			AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-3.0f, 2.0f, 0.0f));
			AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-2.0f, 2.0f, 0.0f));
			AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, 2.0f, 0.0f));

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			m_GameStageCsv.SetFileName(DataDir + L"TestMap6.csv");
			m_GameStageCsv.ReadCsv();

			CreateCsvObjects();

			// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//プレイヤーオブジェクトを追加
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

			// 磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateCsvObjects() {

		const auto& groundGroup = CreateSharedObjectGroup(L"Ground");
		const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;


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
					ptrGround = AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY+5 , 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 1: //磁石N極
					ptrMag = AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 2: //磁石S極
					ptrMag = AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 3: //金属
					ptrMag = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 9://ベルトコンベア右回り端
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 10://ベルトコンベア右回り真ん中
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 11://ベルトコンベア左回り端
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 12://ベルトコンベア左回り真ん中
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 13: //スタート
					ptrGround = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 14: //セーブポイント
					ptrGround = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 15: //ゴール
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				default:
					break;
				}

				//if (isCreateMaagnets) {
				//	magnetsGroup->IntoGroup(ptrMag);
				//}
				//else {
				//	groundGroup->IntoGroup(ptrGround);
				//	isCreateMaagnets = true;
				//}
				//magnetsGroup->IntoGroup(ptrMag);
				//groundGroup->IntoGroup(ptrGround);


			}
		}
		magnetsGroup->IntoGroup(ptrMag);
		groundGroup->IntoGroup(ptrGround);

	}

}
//end basecross
