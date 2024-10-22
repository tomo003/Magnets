/*!
@file SaveObject.cpp
@brief セーブオブジェクト
@autor 吉田鈴
@detail セーブオブジェクトやその周辺のオブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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
			2, 1, 3,
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
		float rot = Utility::Lerp(start, end, m_ratio); // スタートの角度から終わりの角度まで線形補間関数
		m_ratio += m_rotateSpeed * delta / abs(end - start);
		// 線形補間の割合が1以下だったら
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
			2, 1, 3,
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
		float rot = Utility::Lerp(start, end, m_ratio); // スタートの角度から終わりの角度まで線形補間関数
		m_ratio += m_rotateSpeed * delta / abs(end - start); 
		// 線形補間の割合が1以下だったら
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

		SetAlphaActive(true);

		SetDrawLayer(5);
	}

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

		// セーブオブジェクトの上の板ポリの追加
		m_ptrTriangleRed = GetStage()->AddGameObject<SaveTriangleRed>
			(Vec3(1.0f), Vec3(transComp->GetPosition().x , transComp->GetPosition().y + 4.5f, transComp->GetPosition().z));
		m_ptrTriangleBlue = GetStage()->AddGameObject<SaveTriangleBlue>
			(Vec3(1.0f), Vec3(transComp->GetPosition().x , transComp->GetPosition().y + 4.5f, transComp->GetPosition().z));
		// セーブオブジェクトの上の文字の追加
		GetStage()->AddGameObject<SavePointTexture>(Vec3(3.0f, 0.75f, 1.0f), Vec3(transComp->GetPosition().x, transComp->GetPosition().y + 6.5f, transComp->GetPosition().z));
	}

	void SavePoint::OnUpdate()
	{
		// 両方のプレイヤーに触れたら
		if (isCollPlayer && isCollPlayer2)
		{
			// テクスチャの変更
			auto transComp = GetComponent<Transform>();
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"PURPLE_TX");
			// 上の板ポリを回す
			m_ptrTriangleRed->Rotate();
			m_ptrTriangleBlue->Rotate();
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
	}

	void SavePoint::Reset()
	{
		// プレイヤーのどちらかでも通過していなかったら
		if (!isCollPlayer || !isCollPlayer2)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"GREEN_TX");
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

		// プレイヤー１が右側に通り抜けたら
		if (ptrPlayer && ptrPos.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer) {
			isCollPlayer = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"RED_TX");
			m_ptrTriangleRed->ChangeTexture(L"TRIANGLERED_TX");
			XAPtr->Start(L"SAVE_SE", 0, 3.0f);
		}
		// プレイヤー２が右側に通り抜けたら
		if (ptrPlayer2 && ptrPos.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer2) {
			isCollPlayer2 = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"BLUE_TX");
			m_ptrTriangleBlue->ChangeTexture(L"TRIANGLEBLUE_TX");
			XAPtr->Start(L"SAVE_SE", 0, 3.0f);
		}
	}
}