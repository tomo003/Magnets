/*!
@file MoveMagnetsObject.h
@brief 移動式磁石オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveMagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3
		};

	private:
		enum EState m_eMagPole = EState::eMetal;	// 磁極の状態

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_position;
		float m_speed;

		std::vector<Vec3> m_points; // 巡回ポイント
		int m_currentPointIndex; // 現在の移動ライン番号

	public:
		MoveMagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(EState::eMetal),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		// プレイヤーに磁力による力を適用
		void ApplyForcePlayer();
	};

	class MoveMetalObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3
		};

	private:
		enum EState m_eMagPole = EState::eMetal;	// 磁極の状態

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント
		std::shared_ptr<MagnetArea> m_ptrArea;

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_position;
		float m_speed;

		const std::vector<Vec3> m_points = {
			Vec3(m_position.x +3.5f, m_position.y, 0.0f), // 左
			Vec3(m_position .x -3.5f, m_position.y, 0.0f) // 右
		};

		// 巡回ポイント
		int m_currentPointIndex; // 現在の移動ライン番号
		std::shared_ptr<EffectPlayer> m_efk;
		bool isEfkMove = true;
	public:
		MoveMetalObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(EState::eMetal),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();
		void OnDestroy()override;

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		// プレイヤーに磁力による力を適用
		void ApplyForcePlayer();
		void EfkStop();
	};
}