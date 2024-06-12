/*!
@file GoalObject.h
@brief �S�[���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�S�[���A���X�|�[���n�_�̏�̎l�p��
	class Guide : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		int m_Number;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		Guide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const int& Number
		);
		virtual ~Guide();
		virtual void OnCreate() override;
	};
}
