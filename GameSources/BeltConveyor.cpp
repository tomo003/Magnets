/*!
@file BeltConveyor.cpp
@brief ベルトコンベアーの実装
@author 佐藤悠
@detail　ベルトコンベアの中央部の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	左方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	BeltConveyorLeft::BeltConveyorLeft(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	BeltConveyorLeft::~BeltConveyorLeft() {}

	void BeltConveyorLeft::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		AddTag(L"BeltConveyorLeft");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.5f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"CONVEYOR");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"normal", 0, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"normal");

		auto group = GetStage()->GetSharedObjectGroup(L"BeltConveyorLeft");
		group->IntoGroup(GetThis<GameObject>());
	}

	void BeltConveyorLeft::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}

	void BeltConveyorLeft::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		auto anime = ptrDraw->GetCurrentAnimation();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto pos = GetComponent<Transform>()->GetPosition();
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto playerPos2 = ptrPlayer2->GetComponent<Transform>()->GetPosition();

		if (length(playerPos - pos) > 5.0f && length(playerPos2 - pos) > 5.0f) {
			//SetUpdateActive(false);
			//SetDrawActive(false);
		}

	}
	//--------------------------------------------------------------------------------------
	//	右方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	BeltConveyorRight::BeltConveyorRight(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	BeltConveyorRight::~BeltConveyorRight() {}

	void BeltConveyorRight::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		AddTag(L"BeltConveyorRight");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.5f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"CONVEYOR");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"normal", 70, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"normal");

		auto group = GetStage()->GetSharedObjectGroup(L"BeltConveyorRight");
		group->IntoGroup(GetThis<GameObject>());
	}

	void BeltConveyorRight::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}

	void BeltConveyorRight::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		auto anime = ptrDraw->GetCurrentAnimation();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto pos = GetComponent<Transform>()->GetPosition();
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto playerPos2 = ptrPlayer2->GetComponent<Transform>()->GetPosition();

		if (length(playerPos - pos) > 10.0f && length(playerPos2 - pos) > 10.0f) {
			//SetUpdateActive(false);
			//SetDrawActive(false);
		}

	}

}
//end basecross