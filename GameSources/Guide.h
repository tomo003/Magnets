/*!
@file Guide.h
@brief 道案内の板ポリ
@autor 吉田鈴
@detail ゲームステージで道を示す板ポリの実体
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゴール、リスポーン地点の上の四角赤
	class Guide : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		int m_Number; // 何番目のテクスチャか示す変数

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		// 構築と破棄
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
		// 初期化
		virtual void OnCreate() override;
	};
}
