/* !
@file BackGroundSprite.h
@brief ”wŒi‚ÌÀ‘•
@author ²“¡—I
@detail@ƒ^ƒCƒgƒ‹‚âƒQ[ƒ€ƒXƒe[ƒW‚Å‚Ì”wŒi‚ğÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//‰æ‘œƒ‹[ƒv‚Ì”wŒi
	//--------------------------------------------------------------------------------------
	void BackGroundSprite::OnCreate(){
		m_mesh = MeshResource::CreateCube(10.0f, true);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_tex);
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);

		const Vec3 scale(200.00f, 30.0f, 1.0f);
		auto transComp = AddComponent<Transform>();
		transComp->SetScale(scale);
		transComp->SetPosition(Vec3(0.0f, 5.0f, 10.0f));

		SetDrawLayer(-3);

		auto vertices = m_mesh->GetBackupVerteces<VertexPositionNormalTexture>();
		for (auto& vertex : vertices) { 
			if (vertex.normal.z < 0.0f || vertex.normal.z > 0.0f){ // ‘OŒã
				vertex.textureCoordinate.x *= scale.x;
				vertex.textureCoordinate.y *= scale.y;
			}
			if (vertex.normal.x < 0.0f || vertex.normal.x > 0.0f){ // ¶‰E
				vertex.textureCoordinate.x *= scale.z;
				vertex.textureCoordinate.y *= scale.y;
			}
			if (vertex.normal.y < 0.0f || vertex.normal.y > 0.0f){ // ã‰º
				vertex.textureCoordinate.x *= scale.x;
				vertex.textureCoordinate.y *= scale.z;
			}
		}

		m_mesh->UpdateVirtexBuffer<VertexPositionNormalTexture>(vertices);
	}

	//--------------------------------------------------------------------------------------
	//‰æ‘œ‚²‚Æ‚Ì”wŒi
	//--------------------------------------------------------------------------------------
	void BackGroundSprite2::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_texkey);
		
		auto trans = AddComponent<Transform>();
		trans->SetScale(Vec3(m_scale.x,m_scale.y,1.0f));
		trans->SetPosition(Vec3(m_position.x, m_position.y, 10.0f+m_position.z));

		SetDrawLayer(-3);
	}

	void BackGroundSprite2::OnUpdate() {

	}

}