/* !
@file TitleSprite.h
@brief タイトルシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BackGroundSprite::OnCreate(){
		m_mesh = MeshResource::CreateCube(1.0f, true);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetTextureResource(L"BACKGROUND");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);

		const Vec3 scale(100.0f, 50.0f, 1.0f);
		auto transComp = AddComponent<Transform>();
		transComp->SetScale(scale);
		transComp->SetPosition(Vec3(0.0f, 0.0f, 0.0f));

		auto vertices = m_mesh->GetBackupVerteces<VertexPositionNormalTexture>();
		for (auto& vertex : vertices) { 
			if (vertex.normal.z < 0.0f || vertex.normal.z > 0.0f){ // 前後
				vertex.textureCoordinate.x *= scale.x;
				vertex.textureCoordinate.y *= scale.y;
			}
			if (vertex.normal.x < 0.0f || vertex.normal.x > 0.0f){ // 左右
				vertex.textureCoordinate.x *= scale.z;
				vertex.textureCoordinate.y *= scale.y;
			}
			if (vertex.normal.y < 0.0f || vertex.normal.y > 0.0f){ // 上下
				vertex.textureCoordinate.x *= scale.x;
				vertex.textureCoordinate.y *= scale.z;
			}
		}

		m_mesh->UpdateVirtexBuffer<VertexPositionNormalTexture>(vertices);
		//Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 10.0f), m_DefaultSize, L"BACKGROUND");

	}

	void BackGroundSprite::OnUpdate() {
		Sprites::OnUpdate();
	}
}