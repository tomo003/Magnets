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
		const Vec3 eye(0.0f, 4.0f, -15.0f);
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

	void StandbyStage::CreateObjGroup() {
		CreateSharedObjectGroup(L"BeltConveyorLeft");
		CreateSharedObjectGroup(L"BeltConveyorRight");
		CreateSharedObjectGroup(L"BeltConveyorSideLeft");
		CreateSharedObjectGroup(L"BeltConveyorSideRight");
	}

	void StandbyStage::PlayBGM() {
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"STANDBY_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void StandbyStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}


	void StandbyStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//BGMの再生
			PlayBGM();
			//AddGameObject<BackGroundSprite>();
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(0, 0, 0), L"BACKGROUND1");

			//CreateObjGroup();

			// 地面のオブジェクトを追加
			AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));
			
			AddGameObject<Ground>(Vec3(1.0f, 3.0f, 1.0f), Vec3(15.0f, 1.0f, 0.0f));
			AddGameObject<Ground>(Vec3(4.0f, 1.0f, 1.0f), Vec3(16.5f, 3.0f, 0.0f));
			AddGameObject<Ground>(Vec3(1.0f, 3.0f, 1.0f), Vec3(18.0f, 1.0f, 0.0f));

			//プレイヤーオブジェクトを追加
			m_ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", m_ptrPlayer);
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(16.0f, 1.0f, 0.0f));
			m_ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", m_ptrPlayer2);
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(16.0f, 0.0f, 0.0f));
			
			const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

			m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-600.0f, -50.0f, 0.0f),L"BPUSH");
			m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-200.0f, -50.0f, 0.0f), L"BPUSH");

			// 磁石オブジェクトを追加
			m_ptrMagObjS = AddGameObject<MagnetS>(Vec3(1.0f), Vec3(-3.0f, 1.8f, 0.0f));
			m_ptrMagObjN = AddGameObject<MagnetN>(Vec3(1.0f),Vec3(3.0f, 1.8f, 0.0f));

			magnetsGroup->IntoGroup(m_ptrMagObjN);
			magnetsGroup->IntoGroup(m_ptrMagObjS);

		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {
		//プレイヤーの重力を0に変更
		m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
		m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();

		auto device = App::GetApp()->GetInputDevice();//コントローラー座標の取得
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();//|| KeyState.m_bPressedKeyTbl[VK_SPACE]
		//プレイヤー１
		if (firstPad.wPressedButtons & XINPUT_GAMEPAD_B) {
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-3.0f, -1.5f, 0.0f));
			m_ptrBbuttonSprite->SetDrawActive(false);
			m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-600.0f, -50.0f, 0.0f), L"RBPUSH");
			playerBPush = true;
		}
		if (playerBPush && !playerReady) {
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-3.0f, -1.5f, 0.0f));
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");;
		}
		if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (playerBPush) {
				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-600.0f, -50.0f, 0.0f), L"READY");
				playerReady = true;
			}
		}
		Vec3 playerPos = m_ptrPlayer->GetComponent<Transform>()->GetPosition();
		if (playerPos.y > 0.80f && playerReady&& !playerPositionFixed) {
			AddGameObject<EffectPlayer>(playerPos, Vec3(1.0f), L"impact");
			playerPositionFixed = true;
		}
		if (playerReady && playerPositionFixed) {
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(-3.0f, 0.8f, 0.0f));
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRed_MESH");
		}
		//プレイヤー２
		if (secondPad.wPressedButtons & XINPUT_GAMEPAD_B|| firstPad.wPressedButtons & XINPUT_GAMEPAD_X) {
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Brack_MESH");
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0f, -1.5f, 0.0f));
			m_ptrBbuttonSprite2->SetDrawActive(false);		
			m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-200.0f, -50.0f, 0.0f), L"RBPUSH");
			player2BPush = true;
		}
		if (player2BPush && !player2Ready) {
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0f, -1.5f, 0.0f));
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Brack_MESH");
		}
		if (secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER|| firstPad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			if (player2BPush) {
				m_ptrBbuttonSprite2->SetDrawActive(false);
				m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-200.0f, -50.0f, 0.0f), L"READY");
				player2Ready = true;
			}
		}
		Vec3 player2Pos = m_ptrPlayer2->GetComponent<Transform>()->GetPosition();
		if (player2Pos.y >= 0.8f && player2Ready&& !player2PositionFixed) {
			AddGameObject<EffectPlayer>(player2Pos, Vec3(1.0f), L"impact");
			player2PositionFixed = true;
		}
		if (player2Ready && player2PositionFixed) {
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0f, 0.8f, 0.0f));
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBlue_MESH");;
		}

		//シーン遷移
		if (playerReady && player2Ready) {
			float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
			float speed = delta * 6.5f;
			m_time -= delta;

			if (m_time < 0.0f) {
				Vec3 magNPos = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();
				Vec3 magSPos = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();

				m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x + speed, magNPos.y, magNPos.z));
				m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x + speed, magSPos.y, magSPos.z));
				m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x, magNPos.y - 1.0f, magNPos.z));
				m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x, magSPos.y - 1.0f, magSPos.z));

				m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBlue_MESH");;
				m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Red_MESH");;

				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite2->SetDrawActive(false);

				if (magNPos.x > 10.0f) {
					if (!stage) {
						//AddGameObject<FadeIn>(L"FADE_BLACK");
						AddGameObject<FadeOut>(L"FADE_WHITE");
						//AddGameObject<FadeOut>(L"FADE_BLACK");
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						stage = true;
					}
				}
			}
		}
	}

}
//end basecross