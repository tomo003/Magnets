/*!
@file BeltConveyor.cpp
@brief �x���g�R���x�A�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�E�����̖��
	//--------------------------------------------------------------------------------------
		//�S�[���̏�̎l�p���ݒu
	RightGuide::RightGuide(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	RightGuide::~RightGuide() {}

	void RightGuide::OnCreate()
	{
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-0.7f, +0.7f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+0.7f, +0.7f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-0.7f, -0.7f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+0.7f, -0.7f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"GUIDER_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	�������̖��
	//--------------------------------------------------------------------------------------
		//�S�[���̏�̎l�p���ݒu
	LeftGuide::LeftGuide(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	LeftGuide::~LeftGuide() {}

	void LeftGuide::OnCreate()
	{
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-0.7f, +0.7f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+0.7f, +0.7f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-0.7f, -0.7f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+0.7f, -0.7f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"GUIDEL_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);
	}

}