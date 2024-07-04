/*!
@file StartMoveObject.cpp
@brief ゲームステージ開始時プレイヤーを運んでくるオブジェクト
@autor 吉田鈴
@detail ゲームステージ開始時プレイヤーを運んでくるオブジェクトや登場時のプレイヤーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// ゲームステージ開始時プレイヤーを運んでくるオブジェクト
	//--------------------------------------------------------------------------------------
	void StartMoveObject::OnCreate()
	{
		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		// 磁石オブジェクトを追加
		m_ptrMagObjS = GetStage()->AddGameObject<ChangeTextureBlock>(Vec3(1.0f), Vec3(ptrStartPos.x-15, ptrStartPos.y + 5, 0.0f), L"MGNETS_TX");
		m_ptrMagObjN = GetStage()->AddGameObject<ChangeTextureBlock>(Vec3(1.0f), Vec3(ptrStartPos.x-10, ptrStartPos.y + 5, 0.0f), L"MGNETN_TX");

		// 磁石オブジェクトのポジションを取得
		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		// プレイヤーオブジェクトの取得
		m_ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		// プレイヤーをマグネットの下に移動
		m_ptrPlayer->GetComponent<Transform>()->SetPosition(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z);
		m_ptrPlayer2->GetComponent<Transform>()->SetPosition(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z);

		// カメラをスタートカメラに設定しておく
		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->StartCamera();
	}

	void StartMoveObject::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
		float speed = delta * 6.5f;

		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		auto device = App::GetApp()->GetInputDevice();// コントローラー座標の取得
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		// スタートオブジェクトの位置の取得
		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		// プレイヤーが離れていなかったら
		if (!leavePlayer)
		{
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRed_MESH");
			m_ptrPlayer->SetPlayerMagPole(STATE_NONE);
		}
		// プレイヤー2が離れていなかったら
		if (!leavePlayer2)
		{
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Blue_MESH");
			m_ptrPlayer2->SetPlayerMagPole(STATE_NONE);
		}
		// プレイヤーが離れていなくてスタートポジションにだとりついていなかったら
		if (((ptrMagenetPosN.x + ptrMagenetPosS.x)/2) < ptrStartPos.x && !leavePlayer && !leavePlayer2)
		{
			// 稼働音が流れていなかったら
			if (!OperationSEPlay)
			{
				m_operationSound = XAPtr->Start(L"OPERATION_SE", 0, 2.0f);
				OperationSEPlay = true;
			}

			// プレイヤーの重力を0に変更
			m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
			m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
			// スタートポジションまで移動させる
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y, ptrMagenetPosS.z));
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
		}
		// 磁石がスタートポジションにたどり着いたら
		else if (((ptrMagenetPosN.x + ptrMagenetPosS.x) / 2) >= ptrStartPos.x )
		{
			// 音が止まっていなかったら
			if (!StopSEPlay)
			{
				XAPtr->Stop(m_operationSound);
				XAPtr->Start(L"STOP_SE", 0, 3.0f);
				StopSEPlay = true;
				OperationSEPlay = false;
			}
			// プレイヤーが離れていなかったら
			if (!leavePlayer)
			{
				m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
				m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
			}
			// プレイヤー２が離れていなかったら
			if (!leavePlayer2)
			{
				m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
				m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			}

			// プレイヤーがRBボタンを押したら
			if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				// プレイヤーが離れていなかったら
				if (!leavePlayer) {
					leavePlayer = true;
					m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					m_ptrPlayer->SetPlayerMagPole(STATE_NONE);
				}
			}
			// プレイヤー２がRBボタンを押したら
			if (secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				// プレイヤー２が離れていなかったら
				if (!leavePlayer2) {
					leavePlayer2 = true;
					m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					m_ptrPlayer2->SetPlayerMagPole(STATE_NONE);
				}
			}
		}

		// プレイヤーが両方とも磁石から離れたら
		if (leavePlayer && leavePlayer2){
			// 稼働音が流れていなかったら
			if (!OperationSEPlay)
			{
				m_operationSound = XAPtr->Start(L"KADOU_SE", 0, 1.0f);
				OperationSEPlay = true;
			}

			// カメラをゲームプレイ用に変更
			auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
			ptrDuoCamera->MoveCamera();

			// 磁石が帰っていく
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x - speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x - speed, ptrMagenetPosS.y, ptrMagenetPosS.z));

			// 磁石が返ったら磁石を消す
			if (ptrMagenetPosN.x < -20)
			{
				XAPtr->Stop(m_operationSound);
				m_ptrMagObjN->OnDestroy();
				m_ptrMagObjS->OnDestroy();
			}
		}
	}
}