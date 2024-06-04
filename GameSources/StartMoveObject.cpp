/*!
@file StartMoveObject.cpp
@brief 
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//ステージの通常ブロックの仮設置
	StartMoveObject::StartMoveObject(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	StartMoveObject::~StartMoveObject() {}

	void StartMoveObject::OnCreate()
	{
		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		// 磁石オブジェクトを追加
		m_ptrMagObjS = GetStage()->AddGameObject<ChangeTextureBox>(Vec3(1.0f), Vec3(ptrStartPos.x-15, ptrStartPos.y + 5, 0.0f));
		m_ptrMagObjN = GetStage()->AddGameObject<ChangeTextureBox>(Vec3(1.0f), Vec3(ptrStartPos.x-10, ptrStartPos.y + 5, 0.0f));

		m_ptrMagObjS->ChangeTexture(L"MGNETS_TX");
		m_ptrMagObjN->ChangeTexture(L"MGNETN_TX");

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		ptrPlayer->GetComponent<Transform>()->SetPosition(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z);

		ptrPlayer2->GetComponent<Transform>()->SetPosition(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z);

		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->StartCamera();
	}

	void StartMoveObject::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
		float speed = delta * 6.5f;

		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		auto device = App::GetApp()->GetInputDevice();//コントローラー座標の取得
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		//プレイヤーがくっついていたら
		if (!leavePlayer)
		{
			ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRed_MESH");
			ptrPlayer->SetPlayerMagPole(3);
		}
		if (!leavePlayer2)
		{
			ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBlue_MESH");
			ptrPlayer2->SetPlayerMagPole(3);
		}
		//プレイヤーが離れていなくてスタートポジションにだとりついていなかったら
		if (((ptrMagenetPosN.x + ptrMagenetPosS.x)/2) < ptrStartPos.x && !leavePlayer && !leavePlayer2)
		{
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 2.0f);
				MoveSEPlay = true;
			}

			//プレイヤーの重力を0に変更
			ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
			ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
			//スタートポジションまで移動させる
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y, ptrMagenetPosS.z));
			ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
		}
		//磁石がスタートポジションにたどり着いたら
		else if (((ptrMagenetPosN.x + ptrMagenetPosS.x) / 2) >= ptrStartPos.x )
		{
			if (!StopSEPlay)
			{
				XAPtr->Stop(m_kadouonn);
				XAPtr->Start(L"STOP_SE", 0, 3.0f);
				StopSEPlay = true;
				MoveSEPlay = false;
			}
			if (!leavePlayer)
			{
				ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
				ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
			}
			if (!leavePlayer2)
			{
				ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
				ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			}

			//磁力を変更したら(RBボタンを押したら)
			if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				if (!leavePlayer) {
					leavePlayer = true;
					ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					ptrPlayer->SetPlayerMagPole(3);
				}
			}

			if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				if (!leavePlayer2) {
					leavePlayer2 = true;
					ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					ptrPlayer2->SetPlayerMagPole(3);
				}
			}

		}

		//プレイヤーが磁石から離れたら
		if (leavePlayer && leavePlayer2){
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 1.0f);
				MoveSEPlay = true;
			}

			//カメラをゲームプレイ用に変更
			auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
			ptrDuoCamera->MoveCamera();
			//磁石が帰っていく
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x - speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x - speed, ptrMagenetPosS.y, ptrMagenetPosS.z));

			//磁石が返ったら磁石を消す
			if (ptrMagenetPosN.x < -20)
			{
				XAPtr->Stop(m_kadouonn);
				m_ptrMagObjN->OnDestroy();
				m_ptrMagObjS->OnDestroy();
			}
		}
		else {
		}

	}
}