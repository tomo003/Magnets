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
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			m_GameStageCsv.SetFileName(DataDir + L"TestMap1.csv");
			m_GameStageCsv.ReadCsv();

			CreateCsvObjects();

			// 地面のオブジェクトを追加
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

			//プレイヤーオブジェクトを追加
			AddGameObject<Player>();

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateCsvObjects() {

		const auto& groundGroup = CreateSharedObjectGroup(L"Ground");

		float size = 5;
		Vec3 objScale = Vec3(1.0f) / size;

		auto& LineVec = m_GameStageCsv.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				float posX = (float)((int)j - 20) / size;
				float posY = (float)((int)i) / size;

				if (Tokens[j] == L"0") {
					//groundGroup->IntoGroup(AddGameObject<Ground>(Vec3(1.0f) / size, Vec3(posX, -posY - 3.0f, 0)));
				}
				if (Tokens[j] == L"1") {
				}
			}
		}
	}

}
//end basecross
