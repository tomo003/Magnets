#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, 0.5)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, 0.5)

namespace basecross {

	void MagnetArea::OnCreate()
	{
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
			0, 1, 2,  // vertices�̗v�f�ԍ��ɑΉ�(�ԍ����w�����_��3���g�ɂ��ă|���S�������)
			2, 1, 3,   // �Q�[���Ń|���S���͂��ׂĎO�p
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		// PT => Position,Texture
		drawComp->SetOriginalMeshUse(true); // ���b�V�������삷��
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