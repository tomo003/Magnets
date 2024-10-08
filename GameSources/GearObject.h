/*!
* @file GearObject.h
* @brief 歯車オブジェクト
* @author 穴澤委也
* @details 歯車オブジェクトと歯車に付属している床
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	//----------------歯車オブジェクトの床-------------------------------------------
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

		float m_ObjMass = 1.0f; // オブジェクトの重さ(引力で使用)
		float m_MagAreaRadius = 3.0f; // 磁力を適用する範囲

		Vec3 m_position; // 位置
		Vec3 m_posDiff = Vec3(0.0f, 4.5f, 0.0f); // 生成時の位置から正規の位置までの差分
		Vec3 m_Rotation = Vec3(0.0f); // 回転はゼロ
		Vec3 m_Scale = Vec3(3.5f, 1.0f, 1.0f); // サイズ

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

		/**
		* @fn void RotToCenter()
		* @brief 中心をもとに回転する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void RotToCenter();

		/**
		* @fn void RotToCenter()
		* @brief 磁力状態を渡す関数
		* @param　引数なし
		* @return int enumをint型にして渡す
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}

		/**
		* @fn float GetMass()
		* @brief オブジェクトの重さを渡す関数
		* @param 引数なし
		* @return float オブジェクトの重さ
		*/
		float GetMass() {
			return m_ObjMass;
		}

		/**
		* @fn float GetAreaRadius()
		* @brief 磁気エリアの範囲を渡す関数
		* @param 引数なし
		* @return float 磁気エリアの半径
		*/
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		/**
		* @fn void ApplyForcePlayer()
		* @brief プレイヤーに磁力を適用する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void ApplyForcePlayer();

		/**
		* @fn void ApplyForceSecondPlayer()
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

	//----------------歯車オブジェクト------------------------------------------------------
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

		float m_floorDiffY = 4.0f;

		// コンポーネント取得省略用
		shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.2f); // ちょっとだけ奥に配置
		Vec3 m_Rotation = Vec3(0.0f);
		Vec3 m_Scale = Vec3(7.0f);

		float m_RotSpeed; // 一秒で50度回す
		int m_RotDir; // 回転方向(1 = 左回転、-1 = 右回転)
	public:
		GearObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const int& RotDir,
			const float& RotSpeed,
			const int& fisetFloorState,
			const int& secondFloorState
			) :
			GameObject(stage),
			m_position(position),
			m_RotDir(RotDir), // 回転方向
			m_RotSpeed(RotSpeed), // 秒間何度回転するか(Deg)
			m_eFloorStateF(fisetFloorState), // 一個目の床の属性
			m_eFloorStateS(secondFloorState) // 二個目の床の属性
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};
	//--------------------------------------------------------------------------------------
}