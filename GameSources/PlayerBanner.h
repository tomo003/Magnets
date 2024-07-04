/*!
@file PlayerBanner.h
@brief プレイヤーのバナーの実装
@author 佐藤悠
@detail　プレイヤーの上のバナーを実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBanner : public GameObject
	{
		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PTStaticDraw> m_DrawComp; // ドローコンポーネント

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		Vec3 m_playerPos = Vec3(0);// プレイヤーの座標

		wstring m_texKey; // テクスチャ

	public:

		PlayerBanner(const std::shared_ptr<Stage>& stage,const wstring& tex) :
			GameObject(stage),
			m_texKey(tex)
		{}

		void OnCreate() override;
	};
}