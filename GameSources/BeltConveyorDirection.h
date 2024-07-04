/*!
@file BeltConveyorDirection.h
@brief �x���g�R���x�A�̉�]������\�����
@autor �g�c��
@detail �x���g�R���x�A�̉�]������\�����|���̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �E�����̖��
	//--------------------------------------------------------------------------------------
	class RightGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionColor> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		// �\�z�Ɣj��
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
		// ������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	// �������̖��
	//--------------------------------------------------------------------------------------
	class LeftGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionColor> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		// �\�z�Ɣj��
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
		// ������
		virtual void OnCreate() override;
	};
}
