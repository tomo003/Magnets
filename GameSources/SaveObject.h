/*!
@file SaveObject.h
@brief セーブオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//セーブポイント
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

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
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

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
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
