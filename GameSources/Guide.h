/*!
@file GoalObject.h
@brief ゴールオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゴール、リスポーン地点の上の四角赤
	class Guide : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		int m_Number;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
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
