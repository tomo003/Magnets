/*!
@file BeltConveyorDirection.h
@brief ベルトコンベアの回転方向を表す矢印
@autor 吉田鈴
@detail ベルトコンベアの回転方向を表す矢印板ポリの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void RightGuide::OnCreate()
	{
		// 頂点データ
		const float rgb = 1.0f / 256.0f;
		const Col4 deffColor = Col4(rgb * 255.0f, rgb * 192.0f, 0.0f, 1.0f);
		m_vertices = {
			//  Position,			   Color(col4)
			{Vec3(+0.3f,  0.0f, 0.0f), deffColor}, // 右真ん中:0
			{Vec3(-0.3f, +0.3f, 0.0f), deffColor}, // 左上:1
			{Vec3(-0.3f, -0.3f, 0.0f), deffColor}, // 左下:2
		};

		// 頂点インデックス
		m_indices = {
			0, 2, 1,
		};

		auto drawComp = AddComponent<PCStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	void LeftGuide::OnCreate()
	{
		// 頂点データ
		const float rgb = 1.0f / 256.0f;
		const Col4 deffColor = Col4(rgb * 67.0f, rgb * 165.0f, rgb * 251.0f, 1.0f);
		m_vertices = {
			//  Position,			   Color(col4)
			{Vec3(-0.3f,  0.0f, 0.0f), deffColor}, // 左真ん中:0
			{Vec3(+0.3f, +0.3f, 0.0f), deffColor}, // 右上:1
			{Vec3(+0.3f, -0.3f, 0.0f), deffColor}, // 右下:2
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
		};

		auto drawComp = AddComponent<PCStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}
}