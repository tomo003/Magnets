/*!
@file SaveObject.h
@brief �Z�[�u�I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�Z�[�u�|�C���g
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
	public:
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void ResetTexture();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};

	class SaveTriangleRed :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleRed();
		virtual void OnCreate() override;
		void ChangeTexture(wstring Texture);
	};

	class SaveTriangleBlue :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleBlue();
		virtual void OnCreate() override;
		void ChangeTexture(wstring Texture);
	};

}
