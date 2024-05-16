/* !
@file TitleSprite.h
@brief タイトルシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BackGroundSprite::OnCreate(){
		m_mesh = MeshResource::CreateCube(5.0f, true);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(m_mesh);
		drawComp->SetTextureResource(L"BACKGROUND");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);

		const Vec3 scale(200.00f, 30.0f, 1.0f);
		auto transComp = AddComponent<Transform>();
		transComp->SetScale(scale);
		transComp->SetPosition(Vec3(0.0f, 5.0f, 3.0f));

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
	}

	void BackGroundSprite2::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_texkey);
		
		auto trans = AddComponent<Transform>();
		trans->SetScale(Vec3(m_scale.x,m_scale.y,1.0f));
		trans->SetPosition(Vec3(m_position.x, m_position.y, 10.0f+m_position.z));

	}

	void BackGroundSprite2::OnUpdate() {

	}
}