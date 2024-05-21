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

		float m_ObjMass = 1.0f; // オブジェクトの重量(引力斥力で使用)
		float m_MagAreaRadius = 3.0f; // 磁力エリアの半径

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

		float m_ObjMass = 1.0f; // オブジェクトの重量(引力斥力で使用)
		float m_MagAreaRadius = 3.0f; // 磁力エリアの半径

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

	//動く床用のボタン
	class MoveFloorButton : public GameObject 
	{
		// 稼働状態のステート
		enum class EMoveState {
			eReMove, // 戻る
			eStop,   // 停止
			eMove,   // 移動
		};

		enum EMoveState eMoveState = EMoveState::eStop;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント
		std::shared_ptr<PNTStaticDraw> m_actionComp; //アクションコンポーネント

		Vec3 m_position;
		Vec3 m_scale = Vec3(1.0f, 0.1f, 1.0f);

		Vec3 m_startPos; // 初期位置
		float m_endPosY; // 移動後の位置

		float m_speed = 1.0f;


	public:
		MoveFloorButton(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void SetUp() { // スタート位置と停止位置を設定
			m_startPos  = m_position;
			m_endPosY = m_position.y + m_scale.y;
		}

		bool PlayerOnButton(const Vec3& hitPoint) {
			float scaleYhelf = m_scale.y / 2;
			if (hitPoint.y > m_position.y + scaleYhelf) {
				return true;
			}
			return false;
		}

		/*!
		@brief 衝突した瞬間に呼び出される関数
		@param コリジョンペア(コリジョン情報)
		*/
		void OnCollisionEnter(const CollisionPair& Pair) override;
		void OnCollisionExcute(const CollisionPair& Pair) override;
		void OnCollisionExit(const CollisionPair& Pair) override;
	};

	// ボタンで動く床
	class MoveFloor : public GameObject
	{
		// 稼働状態のステート
		enum class EMoveState {
			eReMove, // 戻る
			eStop,   // 停止
			eMove,   // 移動
		};

		enum EMoveState eMoveState = EMoveState::eStop;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント
		std::shared_ptr<Action> m_actionComp; // アクションコンポーネント

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_MoveDir; // 移動方向

		Vec3 m_startPos; // スタート位置
		Vec3 m_endPos;   // 停止位置

		float m_speed = 2.0f;

	public:
		MoveFloor(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& scale,
			const Vec3& position,
			const Vec3& movedir
		) :
			GameObject(stage),
			m_position(position),
			m_scale(scale),
			m_MoveDir(movedir),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();

		void SetUp() { // スタート位置と停止位置を設定
			m_startPos = m_position;
			m_endPos = m_position + (m_scale * m_MoveDir);
		}

		// 移動床のステート設定用関数
		void FloorActive(const bool& active) {
			if (active) {
				eMoveState = EMoveState::eMove;
			}
			else {
				eMoveState = EMoveState::eReMove;
			}
		}

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}