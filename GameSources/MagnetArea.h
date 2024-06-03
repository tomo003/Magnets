/*!
* @file MagnetsArea.h
* @brief 磁気エリア
* @author 穴澤委也
* @details 磁気エリア用の板ポリ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetArea : public GameObject
	{
		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PTStaticDraw> m_DrawComp; // ドローコンポーネント

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		wstring m_texKey; // テクスチャ
		Vec3 m_pos; // 中心位置
		float m_radius; // 半径

	public:
		
		MagnetArea(const std::shared_ptr<Stage>& stage,
				   const Vec3& pos,
				   const float& radius,
				   const wstring& tex) :
			GameObject(stage),
			m_pos(pos),
			m_radius(radius),
			m_texKey(tex)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}