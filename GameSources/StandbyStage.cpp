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
	void StandbyStage::CreateViewLight() {
		const Vec3 eye(0.0f, 4.0f, -12.0f);
		const Vec3 at(0.0f, 4.0f, 0.0f);
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

	void StandbyStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
		XAPtr->Stop(m_kadouonn);
	}

	void StandbyStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//BGMの再生
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"SHUTTER2_SE", 0, 5.0f);//シャッターが開く音

			//AddGameObject<BackGroundSprite>();
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(0, 0, 0), L"BACKGROUND1");

			for (int j = 0;j < 2;j++)
			{
				for (int i = 0; i < 24; i++)
				{
					// 地面のオブジェクトを追加
					AddGameObject<Block>(Vec3(1.0f), Vec3(i - 12,j , 0.0f), L"GROUND_TX");
				}
			}

			//プレイヤーオブジェクトを追加
			m_ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", m_ptrPlayer);
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-4.0f, 1.0f, 0.0f));
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
			m_ptrPlayer->SetPlayerMagPole(3);
			m_ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", m_ptrPlayer2);
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(4.0f, 1.0f, 0.0f));
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
			m_ptrPlayer2->SetPlayerMagPole(3);

			const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

			m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-750.0f, 50.0f, 0.0f),L"RBPUSH");
			m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-50.0f, 50.0f, 0.0f), L"RBPUSH");

			// 磁石オブジェクトを追加
			m_ptrMagObjS = AddGameObject<MagnetS>(Vec3(1.0f), Vec3(-4.0f, 4.8f, 0.0f));
			m_ptrMagObjN = AddGameObject<MagnetN>(Vec3(1.0f),Vec3(4.0f, 4.8f, 0.0f));

			magnetsGroup->IntoGroup(m_ptrMagObjN);
			magnetsGroup->IntoGroup(m_ptrMagObjS);

			m_sFade = AddGameObject<ShutterSprite>(Vec3(-20, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"NFADE");
			m_nFade = AddGameObject<ShutterSprite>(Vec3(-810, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"NFADE");

		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {
		const Vec3& mLPos = m_nFade->GetPosition();
		const Vec3& mRPos = m_sFade->GetPosition();
		auto delta = App::GetApp()->GetElapsedTime();
		m_Totaltime += delta;//経過時間を取得
		//スタンバイシーンに移行して0.5秒経過してからからシャッタースプライトを生成し今度はシャッターが開く処理
		if (m_Totaltime >= 0.5f && mRPos.x <= 780)
		{
			m_sFade->SetPosition(mRPos + Vec3(delta * 1550.0f, 0.0f, 0.0f));
			m_nFade->SetPosition(mLPos + Vec3(-delta * 1550.0f, 0.0f, 0.0f));
		}

	/*	if (stage && mRPos.x >= 0.0f)
		{
			auto delta = App::GetApp()->GetElapsedTime();
			m_sFade->SetPosition(mRPos - Vec3(delta * 1550.0f, 0.0f, 0.0f));
			m_nFade->SetPosition(mLPos - Vec3(-delta * 1550.0f, 0.0f, 0.0f));
		}*/

		//プレイヤーの重力を0に変更
		m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
		m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();

		auto device = App::GetApp()->GetInputDevice();//コントローラー座標の取得
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();//|| KeyState.m_bPressedKeyTbl[VK_SPACE]
		//プレイヤー１
		if (!playerReady) {
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-4.0f, 2.0f, 0.0f));
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
			m_ptrPlayer->SetPlayerMagPole(3);
		}
		if (m_Totaltime >= 1.2f && firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (!playerReady) {
				m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRedanger_MESH");;
				m_ptrPlayer->SetPlayerMagPole(1);
				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-750.0f, 50.0f, 0.0f), L"READY");
				playerReady = true;
			}
		}
		Vec3 playerPos = m_ptrPlayer->GetComponent<Transform>()->GetPosition();
		if (playerPos.y > 3.8f && playerReady&& !playerPositionFixed) {
			AddGameObject<EffectPlayer>(playerPos, Vec3(1.0f), L"impact");
			App::GetApp()->GetXAudio2Manager()->Start(L"UNION_SE", 0, 1.0f);
			playerPositionFixed = true;
		}
		if (playerReady && playerPositionFixed) {
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-4.0f, 3.8f, 0.0f));
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRedanger_MESH");
		}
		//プレイヤー２
		if (!player2Ready) {
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(4.0f, 2.0f, 0.0f));
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
			m_ptrPlayer2->SetPlayerMagPole(3);
		}
		if (m_Totaltime >= 1.2f && secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (!player2Ready) {
				m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Blueanger_MESH");;
				m_ptrPlayer2->SetPlayerMagPole(2);
				m_ptrBbuttonSprite2->SetDrawActive(false);
				m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-50.0f, 50.0f, 0.0f), L"READY");
				player2Ready = true;
			}
		}
		Vec3 player2Pos = m_ptrPlayer2->GetComponent<Transform>()->GetPosition();
		if (player2Pos.y >3.8f && player2Ready&& !player2PositionFixed) {
			AddGameObject<EffectPlayer>(player2Pos, Vec3(1.0f), L"impact");
			App::GetApp()->GetXAudio2Manager()->Start(L"UNION_SE", 0, 1.0f);
			player2PositionFixed = true;
		}
		if (player2Ready && player2PositionFixed) {
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(4.0f, 3.8f, 0.0f));
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Blueanger_MESH");;
		}

		//シーン遷移
		if (playerReady && player2Ready) {
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
			float speed = delta * 6.5f;
			m_time -= delta;

			if (m_time < 0.0f) {
				if (!OperationSEPlay)
				{
					m_kadouonn = XAPtr->Start(L"OPERATION_SE", 0, 1.0f);
					OperationSEPlay = true;
				}
				Vec3 magNPos = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();
				Vec3 magSPos = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();

				m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x + speed, magNPos.y, magNPos.z));
				m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x + speed, magSPos.y, magSPos.z));
				m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x + speed, magNPos.y - 1.0f, magNPos.z));
				m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x + speed, magSPos.y - 1.0f, magSPos.z));

				m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Blueanger_MESH");;
				m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRedanger_MESH");;

				//m_ptrMagObjN->EfkStop();
				//m_ptrMagObjS->EfkStop();
				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite2->SetDrawActive(false);

				if (magNPos.x > 10.0f) {
					if (!stage) {
						AddGameObject<FadeOut>(L"FADE_WHITE");
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
						stage = true;
					}
				}
			}
		}

		//Start・Backボタン同時押しでタイトルに戻る
		if (firstPad.wButtons & BUTTON_START && firstPad.wButtons & BUTTON_BACK ||
			secondPad.wButtons & BUTTON_START && secondPad.wButtons & BUTTON_BACK) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

}
//end basecross