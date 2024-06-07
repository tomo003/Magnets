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

		// ���_�f�[�^�̐ݒ�(VertexPositionColorTexture)
		vector<VertexPositionTexture> vertices;
		vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-0.5f, +0.5f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+0.5f, +0.5f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-0.5f, -0.5f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+0.5f, -0.5f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,  // vertices�̗v�f�ԍ��ɑΉ�(�ԍ����w�����_��3���g�ɂ��ă|���S�������)
			2, 1, 3,   // �Q�[���Ń|���S���͂��ׂĎO�p
		};

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_pos);
		m_ptrTrans->SetScale(Vec3(m_radius * 1.5f));

		m_DrawComp = AddComponent<PTStaticDraw>();
		m_DrawComp->SetOriginalMeshUse(true); // ���b�V�������삷��
		m_DrawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_DrawComp->SetTextureResource(L"TYPEALL_TX");
		m_DrawComp->SetBlendState(BlendState::Additive);
		m_DrawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.1f));

		//auto ptrMoveMetal = GetStage()->GetSharedGameObject<MoveMetalObject>(L"MoveMetalObj");
		//m_ptrTrans->SetParent(ptrMoveMetal);

		auto effDraw = AddComponent<BcPTStaticDraw>();
		effDraw->SetOriginalMeshUse(true);
		effDraw->CreateOriginalMesh(m_vertices, m_indices);
		effDraw->SetBlendState(BlendState::Additive);
		effDraw->SetTextureResource(L"TYPEALL_N_TX");
		effDraw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));

		auto effDraw2 = AddComponent<BcPCTStaticDraw>();
		effDraw2->SetOriginalMeshUse(true);
		effDraw2->CreateOriginalMesh(vertices, m_indices);
		effDraw2->SetBlendState(BlendState::AlphaBlend);
		effDraw2->SetTextureResource(L"TYPEALL_B_TX");
		effDraw2->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));

		SetAlphaActive(true);
	}
	
	void MagnetArea::OnUpdate() {
	}
}