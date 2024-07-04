/*!
@file Guide.h
@brief ���ē��̔|��
@autor �g�c��
@detail �Q�[���X�e�[�W�œ��������|���̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�S�[���A���X�|�[���n�_�̏�̎l�p��
	class Guide : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		int m_Number; // ���Ԗڂ̃e�N�X�`���������ϐ�

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		// �\�z�Ɣj��
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
		// ������
		virtual void OnCreate() override;
	};
}
