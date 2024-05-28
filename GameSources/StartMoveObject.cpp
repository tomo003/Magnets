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
		// 磁石オブジェクトを追加
		m_ptrMagObjS = GetStage()->AddGameObject<MagnetS>(Vec3(1.0f), Vec3(-3.0f, 1.8f, 0.0f));
		m_ptrMagObjN = GetStage()->AddGameObject<MagnetN>(Vec3(1.0f), Vec3(3.0f, 1.8f, 0.0f));

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		ptrPlayer->GetComponent<Transform>()->SetPosition(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z);

		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		ptrPlayer2->GetComponent<Transform>()->SetPosition(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z);

	}

	void StartMoveObject::OnUpdate()
	{

	}

}