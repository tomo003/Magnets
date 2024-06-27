/*!
@file DeathEffect.h
@brief 死亡時のエフェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DeathEffectImg :public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_moveSpeed = 20.0f;//エフェクトが拡大縮小するスピード
		float m_sec = 0.0f;

	public:
		DeathEffectImg(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~DeathEffectImg();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
	class DeathEffect : public GameObject
	{
		std::shared_ptr<DeathEffectImg> ptrEffect[8];

		std::shared_ptr<Player> m_ptrPlayerF;
		std::shared_ptr<Player2> m_ptrPlayerS;

		float m_speed; // 移動の速さ
		float m_forward[8]; // 移動方向を表す単位ベクトル
		Vec3 m_startPos;

		// プレイヤーへのポインタ
		std::shared_ptr<GameObject> m_owner;
		std::shared_ptr<Transform> m_ptrOwnerTrans;

		float m_time = 2.0f;
		float m_removeDistance = 6.0f;//エフェクトを削除する距離
	public:
		DeathEffect(const std::shared_ptr<Stage>& stage, const shared_ptr<GameObject>& owner) :
			GameObject(stage),
			m_speed(0.1f),
			m_owner(owner)
		{
		}
		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross

