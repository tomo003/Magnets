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
	void PlayerMagTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -15.0f);
		const Vec3 at(0.0f,4.0f,0.0f);
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

	void PlayerMagTestStage::CreateObjGroup(){
		CreateSharedObjectGroup(L"BeltConveyorLeft");
		CreateSharedObjectGroup(L"BeltConveyorRight");
		CreateSharedObjectGroup(L"BeltConveyorSideLeft");
		CreateSharedObjectGroup(L"BeltConveyorSideRight");
	}

	void PlayerMagTestStage::OnCreate() {
		try {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene->SetGameState(GameState::MainGame);
			//ビューとライトの作成
			CreateViewLight();
			CreateObjGroup();

			//AddGameObject<BackGroundSprite>();

			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(3.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(4.0f, 4.0f, 0.0f));

			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-4.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-3.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-2.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, 2.0f, 0.0f));

			// 地面のオブジェクトを追加
			AddGameObject<GameObjectSample>(Vec3(10.0f, 1.0f, 1.0f), Vec3(0.0f, -3.0f, 0.0f));
			AddGameObject<GameObjectSample>(Vec3(10.0f, 1.0f, 1.0f), Vec3(18.0f, -3.0f, 0.0f));
			AddGameObject<GameObjectSample>(Vec3(10.0f, 1.0f, 1.0f), Vec3(-18.0f, -3.0f, 0.0f));

			//プレイヤーオブジェクトを追加
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0, 0.0f, 0.0f));
			SetSharedGameObject(L"Player2", ptrPlayer2);

			const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

			// 磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//ptrMagObj = AddGameObject<MagnetN>(Vec3(1.0f),Vec3(10.0f, -0.5f, 0.0f));

			//magnetsGroup->IntoGroup(ptrMagObj);

			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f), EState::eN);
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			// 動く磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MoveMetalObject>(Vec3(3.5f, 2.0f, 0.0f));
			//auto ptrMagObj = AddGameObject<RingObject>(Vec3(0.0f, 2.0f, 0.0f));

			AddGameObject<Metal>(Vec3(1.0f), Vec3(5.0f, 0.0f, 0.0f));

			AddGameObject<GearObject>(Vec3(-9.0f, 1.0f, 0.0f), ROT_LEFT, STATE_METAL, STATE_NONE);

			AddGameObject<BreakWall>(Vec3(17.0f, -2.0f, 0.0f), Vec3(0.0f));

			auto ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(8.0f, 0.99f, 0.9f), Vec3(17.0f, -3.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
			auto ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(15.0f, -2.5f, 0.0f));
			SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
