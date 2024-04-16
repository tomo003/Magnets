#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, 0.5)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, 0.5)

namespace basecross {

	void MagnetArea::OnCreate()
	{
		// 頂点データの設定(VertexPositionColorTexture)
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,  // verticesの要素番号に対応(番号が指す頂点を3つずつ組にしてポリゴンを作る)
			2, 1, 3,   // ゲームでポリゴンはすべて三角
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		// PT => Position,Texture
		drawComp->SetOriginalMeshUse(true); // メッシュを自作する
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(m_texKey);
		SetAlphaActive(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_pos);
		m_ptrTrans->SetScale(Vec3(m_radius));
	}
	
	void MagnetArea::OnUpdate() {
	}
}