/*!
@file MagnetsObject.h
@brief 磁石オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2 // Ｓ極
		};

	private:
		enum EState m_eMagPole;	// 磁極の状態

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント
 
		float m_ObjMass = 1.0f;

		Vec3 m_position;

		float m_MagAreaRadius = 3.0f;

	public:
		MagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position, const EState& eState) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(eState)
		{}

		virtual void OnCreate();
		virtual void OnUpdate();

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

		void ApplyForcePlayer();
	};

}
//end basecross

