/*!
@file BeltConveyor.cpp
@brief ベルトコンベアー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	右方向の矢印
	//--------------------------------------------------------------------------------------
		//ゴールの上の四角青仮設置
	RightGuide::RightGuide(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	RightGuide::~RightGuide() {}

	void RightGuide::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-0.7f, +0.7f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+0.7f, +0.7f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-0.7f, -0.7f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+0.7f, -0.7f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"GUIDER_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	左方向の矢印
	//--------------------------------------------------------------------------------------
		//ゴールの上の四角青仮設置
	LeftGuide::LeftGuide(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	LeftGuide::~LeftGuide() {}

	void LeftGuide::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-0.7f, +0.7f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+0.7f, +0.7f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-0.7f, -0.7f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+0.7f, -0.7f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"GUIDEL_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);
	}

}