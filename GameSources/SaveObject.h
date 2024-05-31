/*!
@file SaveObject.h
@brief セーブオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class SaveTriangleRed :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f;
	public:
		SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleRed();
		virtual void OnCreate() override;
		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	class SaveTriangleBlue :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f;
	public:
		SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleBlue();
		virtual void OnCreate() override;
		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	class SavePointTexture :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		SavePointTexture(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePointTexture();
		virtual void OnCreate() override;
	};

	//セーブポイント
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<SaveTriangleRed> m_ptrTriangleRed;
		std::shared_ptr<SaveTriangleBlue> m_ptrTriangleBlue;

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

}
