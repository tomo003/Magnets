/*!
@file BeltConveyor.h
@brief ベルトコンベアーの矢印
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class RightGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
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

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		LeftGuide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~LeftGuide();
		virtual void OnCreate() override;
	};
}
