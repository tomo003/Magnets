/*!
@file BeltConveyorDirection.h
@brief �x���g�R���x�A�̉�]������\�����
@autor �g�c��
@detail �x���g�R���x�A�̉�]������\�����|���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void RightGuide::OnCreate()
	{
		// ���_�f�[�^
		const float rgb = 1.0f / 256.0f;
		const Col4 deffColor = Col4(rgb * 255.0f, rgb * 192.0f, 0.0f, 1.0f);
		m_vertices = {
			//  Position,			   Color(col4)
			{Vec3(+0.3f,  0.0f, 0.0f), deffColor}, // �E�^��:0
			{Vec3(-0.3f, +0.3f, 0.0f), deffColor}, // ����:1
			{Vec3(-0.3f, -0.3f, 0.0f), deffColor}, // ����:2
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 2, 1,
		};

		auto drawComp = AddComponent<PCStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	void LeftGuide::OnCreate()
	{
		// ���_�f�[�^
		const float rgb = 1.0f / 256.0f;
		const Col4 deffColor = Col4(rgb * 67.0f, rgb * 165.0f, rgb * 251.0f, 1.0f);
		m_vertices = {
			//  Position,			   Color(col4)
			{Vec3(-0.3f,  0.0f, 0.0f), deffColor}, // ���^��:0
			{Vec3(+0.3f, +0.3f, 0.0f), deffColor}, // �E��:1
			{Vec3(+0.3f, -0.3f, 0.0f), deffColor}, // �E��:2
		};

		// ���_�C���f�b�N�X
		m_indices = {
			0, 1, 2,
		};

		auto drawComp = AddComponent<PCStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}
}