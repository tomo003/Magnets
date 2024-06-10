/*!
@file SaveObject.cpp
@brief セーブオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//セーブの上の三角赤
	SaveTriangleRed::SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SaveTriangleRed::~SaveTriangleRed() {}

	void SaveTriangleRed::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.05f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3( -0.05f, +1.0f, 0.0f), Vec2(0.505f, 0.0f)}, // 右上:1
			{Vec3( -0.05f, -1.0f, 0.0f), Vec2(0.505f, 1.0f)}, // 右下:2
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNTRIANGLERED_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position.x, m_Position.y, m_Position.z);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(5);
	}

	void SaveTriangleRed::Rotate()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();
		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		float start = 0.0f;
		float end = XM_2PI;
		float rot = Utility::Lerp(start, end, m_ratio); // 自作した線形補間関数
		m_ratio += m_rotateSpeed * delta / abs(end - start); // end - startは2点間を結ぶベクトル。その長さは「2点間の距離」となる
		if (m_ratio >= 1.0f)
		{
			m_ratio = 0.0f;
		}
		auto transComp = GetComponent<Transform>();
		transComp->SetRotation(Vec3(0.0f, rot,0.0f));
	}

	void SaveTriangleRed::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//セーブの上の三角青
	SaveTriangleBlue::SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SaveTriangleBlue::~SaveTriangleBlue() {}

	void SaveTriangleBlue::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3( 0.0f, +1.0f, 0.0f), Vec2(0.495f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3( 0.0f, -1.0f, 0.0f), Vec2(0.495f, 1.0f)}, // 左下:2
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNTRIANGLEBLUE_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position.x, m_Position.y, m_Position.z);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(5);
	}

	void SaveTriangleBlue::Rotate()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();
		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		float start = 0.0f;
		float end = XM_2PI;
		float rot = Utility::Lerp(start, end, m_ratio); // 自作した線形補間関数
		m_ratio += m_rotateSpeed * delta / abs(end - start); // end - startは2点間を結ぶベクトル。その長さは「2点間の距離」となる
		if (m_ratio >= 1.0f)
		{
			m_ratio = 0.0f;
		}
		auto transComp = GetComponent<Transform>();
		transComp->SetRotation(Vec3(0.0f, rot, 0.0f));
	}

	void SaveTriangleBlue::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//セーブポイントの文字
	SavePointTexture::SavePointTexture(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SavePointTexture::~SavePointTexture() {}

	void SavePointTexture::OnCreate()
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
		drawComp->SetTextureResource(L"CHECKPOINT_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position.x, m_Position.y, m_Position.z - 1.0f);
		transComp->SetScale(m_Scale);

		SetDrawLayer(5);
		SetAlphaActive(true);
	}

	//ステージのリスポーン地点
	SavePoint::SavePoint(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SavePoint::~SavePoint() {}

	void SavePoint::OnCreate()
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
		drawComp->SetTextureResource(L"GREEN_TX");
		drawComp->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale.x + 2, m_Scale.y + 5, m_Scale.z / (float)3);
		transComp->SetRotation(0.0f, XM_PIDIV2, 0.0f);

		m_ptrTriangleRed = GetStage()->AddGameObject<SaveTriangleRed>
			(Vec3(1.0f), Vec3(transComp->GetPosition().x , transComp->GetPosition().y + 4.5, transComp->GetPosition().z));
		m_ptrTriangleBlue = GetStage()->AddGameObject<SaveTriangleBlue>
			(Vec3(1.0f), Vec3(transComp->GetPosition().x , transComp->GetPosition().y + 4.5, transComp->GetPosition().z));
		GetStage()->AddGameObject<SavePointTexture>(Vec3(3.0f, 0.75f, 1.0f), Vec3(transComp->GetPosition().x, transComp->GetPosition().y + 6.5f, transComp->GetPosition().z));

		AddTag(L"SavePoint");
	}

	void SavePoint::OnUpdate()
	{
		//両方のプレイヤーに触れたら
		if (isCollPlayer && isCollPlayer2)
		{
			auto transComp = GetComponent<Transform>();
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"PURPLE_TX");
			m_ptrTriangleRed->Rotate();
			m_ptrTriangleBlue->Rotate();
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
	}

	void SavePoint::ResetTexture()
	{
		if (!isCollPlayer || !isCollPlayer2)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"SAVEPOINT_TX");
			m_ptrTriangleRed->ChangeTexture(L"TENNSENNTRIANGLERED_TX");
			m_ptrTriangleBlue->ChangeTexture(L"TENNSENNTRIANGLEBLUE_TX");
			isCollPlayer = false;
			isCollPlayer2 = false;
		}
	}

	void SavePoint::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);
		auto ptrPos = GetComponent<Transform>()->GetPosition();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		if (ptrPlayer && ptrPos.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer) {
			isCollPlayer = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"RED_TX");
			m_ptrTriangleRed->ChangeTexture(L"TRIANGLERED_TX");
			XAPtr->Start(L"SAVE_SE", 0, 3.0f);
		}
		if (ptrPlayer2 && ptrPos.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer2) {
			isCollPlayer2 = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"BLUE_TX");
			m_ptrTriangleBlue->ChangeTexture(L"TRIANGLEBLUE_TX");
			XAPtr->Start(L"SAVE_SE", 0, 3.0f);
		}
	}
}