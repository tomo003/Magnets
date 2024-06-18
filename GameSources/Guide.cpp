/*!
@file GoalObject.cpp
@brief �S�[���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�S�[���̏�̎l�p�ԉ��ݒu
	Guide::Guide(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position,
		const int& Number
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Number(Number)
	{
	}
	Guide::~Guide() {}

	void Guide::OnCreate()
	{
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-1.6f, +0.8f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+1.6f, +0.8f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-1.6f, -0.8f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+1.6f, -0.8f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);

		switch (m_Number)
		{
		case 1:
			drawComp->SetTextureResource(L"GUIDEREDUP_TX");
			break;

		case 2:
			drawComp->SetTextureResource(L"GUIDEREDDOWM_TX");
			break;

		case 3:
			drawComp->SetTextureResource(L"GUIDEREDCENTER_TX");
			break;

		case 4:
			drawComp->SetTextureResource(L"GUIDEBLUEUP_TX");
			break;

		case 5:
			drawComp->SetTextureResource(L"GUIDEBLUEDOWM_TX");
			break;

		case 6:
			drawComp->SetTextureResource(L"GUIDEBLUECENTER_TX");
			break;

		default:
			break;
		}

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);
	}
}