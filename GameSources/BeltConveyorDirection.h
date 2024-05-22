/*!
@file BeltConveyor.h
@brief �x���g�R���x�A�[�̖��
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class RightGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		RightGuide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~RightGuide();
		virtual void OnCreate() override;
	};

	class LeftGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		LeftGuide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~LeftGuide();
		virtual void OnCreate() override;
	};
}
