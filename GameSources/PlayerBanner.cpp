/*!
@file PlayerBanner.cpp
@brief プレイヤーのバナーの実装
@author 佐藤悠
@detail　プレイヤーの上のバナーを実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void PlayerBanner::OnCreate(){

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
			0, 1, 2,  
			2, 1, 3,  
		};

		m_DrawComp = AddComponent<PTStaticDraw>();
		m_DrawComp->SetOriginalMeshUse(true); // メッシュを自作する
		m_DrawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_DrawComp->SetTextureResource(m_texKey);
		SetAlphaActive(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(0.5f));
		m_ptrTrans->SetPosition(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z - 1.0f);

		SetDrawLayer(2);
	}
}