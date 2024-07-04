/*!
* @file MagnetsObject.h
* @brief 磁石オブジェクト
* @author 吉田鈴
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	// 磁石オブジェクトのベース(試作)
	class MagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
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
		MagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
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
		void ApplyForceSecondPlayer();
	};

	//--------------------------------------------------------------------------------------
	// N極の磁石オブジェクト
	//--------------------------------------------------------------------------------------
	class MagnetN : public GameObject {
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

		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
		int m_State;
		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetN::MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		MagnetN::~MagnetN() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
	};

	//--------------------------------------------------------------------------------------
	// S極の磁石オブジェクト
	//--------------------------------------------------------------------------------------
	class MagnetS : public GameObject {
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

		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetS::MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		MagnetS::~MagnetS() {}
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
	};
}
//end basecross

