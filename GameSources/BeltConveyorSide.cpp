/*!
@file BeltConveyorSide.cpp
@brief ベルトコンベアーの端
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------
	//左方向のベルトコンベア
	//---------------------------------------------------------------
	BeltConveyorSideLeft::BeltConveyorSideLeft(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	BeltConveyorSideLeft::~BeltConveyorSideLeft() {}

	void BeltConveyorSideLeft::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		AddTag(L"BeltConveyorSideLeft");

		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(1.5f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"SIDE_CONVEYOR");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"reverse", 0, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"reverse");


		auto group = GetStage()->GetSharedObjectGroup(L"BeltConveyorSideLeft");
		group->IntoGroup(GetThis<GameObject>());
	}

	void BeltConveyorSideLeft::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}

	void BeltConveyorSideLeft::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);
		auto anime = ptrDraw->GetCurrentAnimation();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto pos = GetComponent<Transform>()->GetPosition();
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto playerPos2 = ptrPlayer2->GetComponent<Transform>()->GetPosition();

		if (length(playerPos - pos) > 10.0f&& length(playerPos2 - pos) > 10.0f){
			//SetUpdateActive(false);
			//SetDrawActive(false);
		}

	}
	//--------------------------------------------------------------
	//右方向のベルトコンベア
	//---------------------------------------------------------------
	BeltConveyorSideRight::BeltConveyorSideRight(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	BeltConveyorSideRight::~BeltConveyorSideRight() {}

	void BeltConveyorSideRight::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		AddTag(L"BeltConveyorSideRight");

		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(1.5f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"SIDE_CONVEYOR");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"reverse", 70, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"reverse");


		auto group = GetStage()->GetSharedObjectGroup(L"BeltConveyorSideRight");
		group->IntoGroup(GetThis<GameObject>());
	}

	void BeltConveyorSideRight::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}

	void BeltConveyorSideRight::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(delta);
		auto anime = ptrDraw->GetCurrentAnimation();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto pos = GetComponent<Transform>()->GetPosition();
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto playerPos2 = ptrPlayer2->GetComponent<Transform>()->GetPosition();

		if (length(playerPos - pos) > 10.0f && length(playerPos2 - pos) > 10.0f){
			//SetUpdateActive(false);
			//SetDrawActive(false);
		}

	}
}
//end basecross