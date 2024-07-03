/*!
@file GoalObject.h
@brief �S�[���I�u�W�F�N�g
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
		GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareRed();
		//������
		virtual void OnCreate() override;

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
		GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareBlue();
		//������
		virtual void OnCreate() override;

		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<GoalSquareRed> m_ptrSquareRed;
		std::shared_ptr<GoalSquareBlue> m_ptrSquareBlue;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
		bool isDisplaySprite = false;
	public:
		//�\�z�Ɣj��
		Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Goal();
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		void PlayerGoal();
		void GoalReset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};


}
