/*!
@file PlayerBanner.cpp
@brief �v���C���[�̃o�i�[�̎���
@author �����I
@detail�@�v���C���[�̏�̃o�i�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void PlayerBanner::OnCreate(){

		// ���_�f�[�^�̐ݒ�(VertexPositionColorTexture)
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,  
			2, 1, 3,  
		};

		m_DrawComp = AddComponent<PTStaticDraw>();
		m_DrawComp->SetOriginalMeshUse(true); // ���b�V�������삷��
		m_DrawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_DrawComp->SetTextureResource(m_texKey);
		SetAlphaActive(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(0.5f));
		m_ptrTrans->SetPosition(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z - 1.0f);

		SetDrawLayer(2);
	}
}