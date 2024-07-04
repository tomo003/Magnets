/*!
@file BeltConveyorDirection.h
@brief ベルトコンベアの回転方向を表す矢印
@autor 吉田鈴
@detail ベルトコンベアの回転方向を表す矢印板ポリの実態
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// 右方向の矢印
	//--------------------------------------------------------------------------------------
	class RightGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionColor> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		// 構築と破棄
		RightGuide::RightGuide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		RightGuide::~RightGuide() {}
		// 初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	// 左方向の矢印
	//--------------------------------------------------------------------------------------
	class LeftGuide :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionColor> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		// 構築と破棄
		LeftGuide::LeftGuide(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		LeftGuide::~LeftGuide() {}
		// 初期化
		virtual void OnCreate() override;
	};
}
