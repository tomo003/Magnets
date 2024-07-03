/*!
@file GoalObject.cpp
@brief ゴールオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト上の赤い板ポリ
	//--------------------------------------------------------------------------------------
	GoalSquareRed::GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	GoalSquareRed::~GoalSquareRed() {}

	void GoalSquareRed::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNRED_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(2);

		AddTag(L"GoalSquareRed");
	}

	void GoalSquareRed::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト上の青い板ポリ
	//--------------------------------------------------------------------------------------
	GoalSquareBlue::GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	GoalSquareBlue::~GoalSquareBlue() {}

	void GoalSquareBlue::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNBLUE_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(2);

		AddTag(L"GoalSquareBlue");
	}

	void GoalSquareBlue::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト
	//--------------------------------------------------------------------------------------
	Goal::Goal(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	Goal::~Goal() {}

	void Goal::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.7f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"RingObject_MESH");
		drawComp->SetTextureResource(L"RED_TX");
		drawComp->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale.x + 2, m_Scale.y + 7.5, m_Scale.z / (float)3);
		transComp->SetRotation(0.0f, XM_PIDIV2, 0.0f);

		SetAlphaActive(true);

		AddTag(L"Goal");

		//ゴールオブジェクトの上の板ポリの追加
		m_ptrSquareRed = GetStage()->AddGameObject<GoalSquareRed>(Vec3(1.0f), Vec3(m_Position.x - 1, m_Position.y + 7, 0));
		GetStage()->SetSharedGameObject(L"GoalSquareRed", m_ptrSquareRed);
		m_ptrSquareBlue = GetStage()->AddGameObject<GoalSquareBlue>(Vec3(1.0f), Vec3(m_Position.x + 1, m_Position.y + 7, 0));
		GetStage()->SetSharedGameObject(L"GoalSquareBlue", m_ptrSquareBlue);

	}

	void Goal::OnUpdate()
	{
		//両方のプレイヤーに触れたら
		if (isCollPlayer && isCollPlayer2)
		{
			PlayerGoal();
		}
	}

	void Goal::PlayerGoal()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];

		//スプライトの表示
		if (!isDisplaySprite)
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"GOAL_SE", 0, 3.5f);

			GetStage()->AddGameObject<Sprites>()->CreateSprite(Vec3(-400.0f, 250.0f, 0.0f), Vec2(800, 130), L"CLEAR");
			isDisplaySprite = true;

			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene->SetGameState(GameState::GameClear);
		}

		//カメラのゴール後にズーム演出
		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->ZoomCamera();
	}

	void Goal::GoalReset()
	{
		isCollPlayer = false;
		isCollPlayer2 = false;
	}

	void Goal::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		//プレイヤー１が右側に通り抜けたら
		if (ptrPlayer && m_Position.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer) {
			if (!isCollPlayer2)
			{
				XAPtr->Start(L"SAVE_SE", 0, 3.5f);
			}
			isCollPlayer = true;
		}
		//プレイヤー２が右側に通り抜けたら
		if (ptrPlayer2 && m_Position.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer2) {
			if (!isCollPlayer)
			{
				XAPtr->Start(L"SAVE_SE", 0, 3.5f);
			}
			isCollPlayer2 = true;
		}
	}
}

