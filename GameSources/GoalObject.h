/*!
@file GoalObject.h
@brief �S�[���I�u�W�F�N�g
@autor �g�c��
@detail �S�[���I�u�W�F�N�g�₻�̎��ӂ̃I�u�W�F�N�g�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g��̐Ԃ��|��
	//--------------------------------------------------------------------------------------
	class GoalSquareRed : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		//�\�z�Ɣj��
		GoalSquareRed::GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		GoalSquareRed::~GoalSquareRed() {}
		//������
		virtual void OnCreate() override;
		/**
		* @brief �e�N�X�`����ύX����֐�
		* @param (Texture) �K���������e�N�X�`����
		* @return �߂�l�Ȃ�
		*/
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g��̐��|��
	//--------------------------------------------------------------------------------------
	class GoalSquareBlue : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		//�\�z�Ɣj��
		GoalSquareBlue::GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		GoalSquareBlue::~GoalSquareBlue() {}
		//������
		virtual void OnCreate() override;
		/**
		* @brief �e�N�X�`����ύX����֐�
		* @param (Texture) �K���������e�N�X�`����
		* @return �߂�l�Ȃ�
		*/
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<GoalSquareRed> m_ptrSquareRed;   // GoalSquareRed
		std::shared_ptr<GoalSquareBlue> m_ptrSquareBlue; // GoalSquareBlue

		bool isCollPlayer = false;    // �v���C���[���ʂ�߂������̔���
		bool isCollPlayer2 = false;   // �v���C���[2���ʂ�߂������̔���
		bool isDisplaySprite = false; // �X�v���C�g���\������Ă��邩�̔���
	public:
		//�\�z�Ɣj��
		Goal::Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		Goal::~Goal() {}
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		/**
		* @brief �v���C���[�̃S�[����̏������s���֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void PlayerGoal();

		/**
		* @brief �v���C���[�̃S�[���O�Ƀ��Z�b�g����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void GoalReset();

		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};


}
