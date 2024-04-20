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

	void StandbyStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<BackGroundSprite>();

			//CreateObjGroup();

			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(3.0f, 4.0f, 0.0f));
			//AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(4.0f, 4.0f, 0.0f));

			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-4.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-3.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-2.0f, 2.0f, 0.0f));
			//AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, 2.0f, 0.0f));

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
		if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (playerBPush) {
				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite = AddGameObject<ButtonSprite>(Vec3(-600.0f, -50.0f, 0.0f), L"READY");
				playerReady = true;
			}
		}
		//プレイヤー２
		if (secondPad.wPressedButtons & XINPUT_GAMEPAD_B|| firstPad.wPressedButtons & XINPUT_GAMEPAD_A) {
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Brack_MESH");;
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0f, -1.5f, 0.0f));
			m_ptrBbuttonSprite2->SetDrawActive(false);		
			m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-200.0f, -50.0f, 0.0f), L"RBPUSH");
			player2BPush = true;
		}
		if (secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER|| firstPad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			if (player2BPush) {
				m_ptrBbuttonSprite2->SetDrawActive(false);
				m_ptrBbuttonSprite2 = AddGameObject<ButtonSprite>(Vec3(-200.0f, -50.0f, 0.0f), L"READY");
				player2Ready = true;
			}
		}

		//シーン遷移
		if (playerReady && player2Ready) {
			float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
			float speed = delta * 3.0f;
			m_time -= delta;

			if (m_time < 0.0f) {
				Vec3 magNPos = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();
				Vec3 magSPos = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();

				m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x + speed, magNPos.y, magNPos.z));
				m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x + speed, magSPos.y, magSPos.z));
				m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(magNPos.x, magNPos.y - 1.0f, magNPos.z));
				m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(magSPos.x, magSPos.y - 1.0f, magSPos.z));

				m_ptrBbuttonSprite->SetDrawActive(false);
				m_ptrBbuttonSprite2->SetDrawActive(false);

				if (magNPos.x > 20.0f) {
					if (!stage) {
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMagTestStage");
						stage = true;
					}
				}
			}
		}
	}

}
//end basecross