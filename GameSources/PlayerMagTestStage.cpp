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



	void PlayerMagTestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			// 地面のオブジェクトを追加
			AddGameObject<Ground>(Vec3(10.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//プレイヤーオブジェクトを追加
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);

			// 磁石オブジェクトを追加
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f), EState::eN);
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			// 動く磁石オブジェクトを追加
			auto ptrMagObj = AddGameObject<MoveMagnetsObject>(Vec3(3.5f, 2.0f, 0.0f));
			//auto ptrMagObj = AddGameObject<RingObject>(Vec3(0.0f, 2.0f, 0.0f));
			SetSharedGameObject(L"MagnetsObject", ptrMagObj);

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
