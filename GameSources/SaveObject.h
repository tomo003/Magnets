/*!
@file SaveObject.h
@brief �Z�[�u�I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�Z�[�u�I�u�W�F�N�g��̐Ԃ��|��
	//--------------------------------------------------------------------------------------
	class SaveTriangleRed :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f; // �|���̉�]���鑬��
	public:
		//�\�z�Ɣj��
		SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleRed();
		//������
		virtual void OnCreate() override;

		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//�Z�[�u�I�u�W�F�N�g��̐��|��
	//--------------------------------------------------------------------------------------
	class SaveTriangleBlue :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f; // �|���̉�]���鑬��
	public:
		//�\�z�Ɣj��
		SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleBlue();
		//������
		virtual void OnCreate() override;

		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//�Z�[�u�I�u�W�F�N�g��̕����̔|��
	//--------------------------------------------------------------------------------------
	class SavePointTexture :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		//�\�z�Ɣj��
		SavePointTexture(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePointTexture();
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//�Z�[�u�|�C���g
	//--------------------------------------------------------------------------------------
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<SaveTriangleRed> m_ptrTriangleRed;
		std::shared_ptr<SaveTriangleBlue> m_ptrTriangleBlue;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
	public:
		//�\�z�Ɣj��
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		void Reset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};

}
