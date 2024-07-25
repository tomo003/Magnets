/*!
@file DeathEffect.h
@brief 死亡時のエフェクト
@autor 吉田鈴
@detail プレイヤーの死亡時に出る飛び散るエフェクトの実態
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// プレイヤー死亡時に飛び散る板ポリ
	//--------------------------------------------------------------------------------------
	class DeathEffectImg :public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_moveSpeed = 20.0f;//エフェクトが拡大縮小するスピード
		float m_sec = 0.0f;

	public:
		// 構築と破棄
		DeathEffectImg::DeathEffectImg(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		DeathEffectImg::~DeathEffectImg() {}
		// 初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	// プレイヤー死亡時に板ポリが飛び散る処理
	//--------------------------------------------------------------------------------------
	class DeathEffect : public GameObject
	{
		std::shared_ptr<Player> m_ptrPlayerF;
		std::shared_ptr<Player2> m_ptrPlayerS;

		std::shared_ptr<DeathEffectImg> ptrEffect[8]; // 配列の要素数は呼び出したいエフェクトの数を入れる

		float m_interval; // エフェクトの飛び散る間隔
		float m_speed; // 移動の速さ
		float m_forward[8] = {0.0f}; // 移動方向を表す単位ベクトル、配列の要素数は呼び出したいエフェクトの数を入れる
		Vec3 m_startPos; // 生成されたポジション

		// プレイヤーへのポインタ
		std::shared_ptr<GameObject> m_owner;
		std::shared_ptr<Transform> m_ptrOwnerTrans;

		float m_time = 2.0f;
		float m_removeDistance = 6.0f; // エフェクトを削除する距離
	public:
		// 構築と破棄
		DeathEffect(const std::shared_ptr<Stage>& stage, const shared_ptr<GameObject>& owner) :
			GameObject(stage),
			m_interval(360/float(size(ptrEffect))),
			m_speed(0.1f),
			m_owner(owner)
		{
		}
		DeathEffect::~DeathEffect() {}
		// 初期化
		void OnCreate() override;

		void OnUpdate() override;
	};
}
//end basecross

