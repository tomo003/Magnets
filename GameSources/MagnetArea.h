/*!
@file MagnetsArea.h
@brief 磁気エリア
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetArea : public GameObject
	{
		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PTStaticDraw> m_ptrDraw; // ドローコンポーネント

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		wstring m_texKey;
		Vec3 m_pos;
		float m_radius;

	public:

		MagnetArea(const std::shared_ptr<Stage>& stage, const Vec3& pos, const float& radius, const wstring& tex) :
			GameObject(stage),
			m_pos(pos),
			m_radius(radius),
			m_texKey(tex)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}