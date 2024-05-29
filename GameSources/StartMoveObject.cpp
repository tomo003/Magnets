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
		auto ptrStartPos = m_ptrStart->GetComponent<Transform>()->GetPosition();

		// 磁石オブジェクトを追加
		m_ptrMagObjS = GetStage()->AddGameObject<MagnetS>(Vec3(1.0f), Vec3(ptrStartPos.x-10, ptrStartPos.y + 5, 0.0f));
		m_ptrMagObjN = GetStage()->AddGameObject<MagnetN>(Vec3(1.0f), Vec3(ptrStartPos.x-4, ptrStartPos.y + 5, 0.0f));

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		m_ptrPlayer->GetComponent<Transform>()->SetPosition(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z);

		m_ptrPlayer2->GetComponent<Transform>()->SetPosition(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z);
	}

	void StartMoveObject::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得
		float speed = delta * 6.5f;

		auto device = App::GetApp()->GetInputDevice();//コントローラー座標の取得
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();
		Vec3 ptrStartPos = m_ptrStart->GetComponent<Transform>()->GetPosition();

		if (!leavePlayer)
		{
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
			m_ptrPlayer->SetPlayerMagPole(3);
		}
		if (!leavePlayer2)
		{
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
			m_ptrPlayer2->SetPlayerMagPole(3);
		}
		if (abs(ptrMagenetPosN.x - ptrMagenetPosS.x) < ptrStartPos.x && leavePlayer)
		{
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y, ptrMagenetPosS.z));
		}

		if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (!leavePlayer) {
				leavePlayer = true;
			}
		}

		if (secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (!leavePlayer2) {
				leavePlayer2 = true;
			}
		}

	}
}