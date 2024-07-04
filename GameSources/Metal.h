/*!
@file Metal.h
@brief 金属オブジェクト
@autor 
@detail ステージの配置されている金属オブジェクトの実体
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// 金属オブジェクト
	//--------------------------------------------------------------------------------------
	class Metal : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

	private:
		enum EState m_eMagPole;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

	public:
		Metal::Metal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		Metal::~Metal() {}
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		virtual int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		virtual float GetMass() {
			return m_ObjMass;
		}
		virtual float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		virtual Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		virtual void ApplyForcePlayer();
		virtual void ApplyForceSecondPlayer();
	};
}
