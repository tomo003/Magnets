/*!
* @file GearObject.h
* @brief 歯車オブジェクト
* @author 穴澤委也
* @details 歯車オブジェクトと歯車に付属している床
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class GearObjFloor : public Metal;
	//--------------------------------------------------------------------------------------
	class GearObjFloor : public GameObject
	{
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
		shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント
		shared_ptr<EffectPlayer> m_efk;

		float m_ObjMass = 1.0f; // オブジェクトの重さ(引力で使用)
		float m_MagAreaRadius = 5.0f; // 磁力を適用する範囲

		Vec3 m_position;
		float m_posDiff = 4.5f;
		Vec3 m_Rotation = Vec3(0.0f);
		Vec3 m_Scale = Vec3(3.5f, 1.0f, 1.0f);

		float m_RotSpeed; // 回転スピード
		int m_RotDir; // 回転方向
	public :
		GearObjFloor(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position, // 位置
			const float& RotSpeed, // 回転スピード
			const int& RotDir, // 回転方向
			const int& state
		):
			GameObject(stage),
			m_position(position),
			m_RotSpeed(RotSpeed),
			m_RotDir(RotDir),
			m_eMagPole(static_cast<EState>(state))
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/*!
		@brief 衝突した瞬間に呼び出される関数
		@param コリジョンペア(コリジョン情報)
		*/
		//void OnCollisionEnter(const CollisionPair& Pair) override;
		//void OnCollisionExcute(const CollisionPair& Pair) override;
		//void OnCollisionExit(const CollisionPair& Pair) override;

		/**
		* @brief 中心をもとに回転する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void RotToCenter();

		/**
		* @brief 磁力状態を渡す関数
		* @param　引数なし
		* @return int enumをint型にして渡す
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}

		/**
		* @brief オブジェクトの重さを渡す関数）
		* @param 引数なし
		* @return float オブジェクトの重さ
		*/
		float GetMass() {
			return m_ObjMass;
		}

		/**
		* @brief 磁気エリアの範囲を渡す関数）
		* @param 引数なし
		* @return float 磁気エリアの半径
		*/
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		/**
		* @brief プレイヤーに磁力を適用する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void ApplyForcePlayer();

		/**
		* @brief プレイヤーに磁力を適用する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void ApplyForceSecondPlayer();

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};

	//--------------------------------------------------------------------------------------
	//	class GearObject : public GameObject;
	//--------------------------------------------------------------------------------------
	class GearObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

	private:
		// GameeObject格納用ポインタ
		shared_ptr<GearObjFloor> m_ptrGearFloorF;
		shared_ptr<GearObjFloor> m_ptrGearFloorS;

		int m_eFloorStateF;
		int m_eFloorStateS;

		// コンポーネント取得省略用
		shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.2f); // ちょっとだけ奥に配置
		Vec3 m_Rotation = Vec3(0.0f);

		float m_RotSpeed = 50; // 一秒で50度回す
		int m_RotDir; // 回転方向(1 = 左回転、-1 = 右回転)
	public:
		GearObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const int& RotDir,
			const int& fisetFloorState,
			const int& secondFloorState
			) :
			GameObject(stage),
			m_position(position),
			m_RotDir(RotDir),
			m_eFloorStateF(fisetFloorState),
			m_eFloorStateS(secondFloorState)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};
}