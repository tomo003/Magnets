/*!
* @file MoveMagnetsObject.h
* @brief 移動式オブジェクトの定義
* @author 穴澤委也
* @details	往復する金属床
*			ボタンで動く床
*			↑用のボタン
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//------------------------往復する金属オブジェクト------------------------------------------------
	class MoveMetalObject : public GameObject
	{
	public:
		// 自身の磁極のステート
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
		float m_MagAreaRadius = 4.5f; // 磁力エリアの半径
		float m_ratio = 0.0f; // 0 ～ 1の係数(0 - 100%)

		Vec3 m_position;
		float m_speed; // 移動スピード
		Vec3 m_moveDir;// 移動方向
		float m_moveVol;// 移動量

		const array<Vec3, 2> m_points;// 巡回ポイント
		int m_currentPointIndex; // 現在の移動ライン番号

	public:
		MoveMetalObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const Vec3& moveDir,
			const float& moveVol) :
			GameObject(stage),
			m_position(position),
			m_moveDir(moveDir),
			m_moveVol(moveVol),
			m_eMagPole(EState::eMetal),
			m_speed(2.0f),
			m_points{Vec3(position + (moveDir * moveVol)), Vec3(position - (moveDir * moveVol))}
		{}

		void OnCreate();
		void OnUpdate();

		/** @brief 磁力の状態をint型で渡す
		*   @fn int GetState()
		*   @param 引数なし
		*   @return int m_eMagPole 
		*   磁力状態をint型にキャストして渡す
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		/** @brief オブジェクトの重さを渡す
		*   @fn float GetMass()
		*   @param 引数なし
		*   @return float 生成時にオブジェクトに設定した重さ
		*/
		float GetMass() {
			return m_ObjMass;
		}
		/** @brief 磁力エリアの半径を渡す関数
		*   @fn float GetAreaRadius()
		*   @param 引数なし
		*   @return float 磁力エリアの半径
		*/
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
		void ApplyForceSecondPlayer();
	};
	//------------------------------------------------------------------------------------------------

	//------------------------動く床用のボタン--------------------------------------------------------
	class MoveFloorButton : public GameObject 
	{
		// 稼働状態のステート
		enum class EMoveState {
			eTurnBack, // 戻る
			eStop,   // 停止
			eMove,   // 移動
		};

		enum EMoveState eMoveState = EMoveState::eStop; // 初期の移動状態は停止

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント
		std::shared_ptr<PNTStaticDraw> m_actionComp; //アクションコンポーネント

		Vec3 m_position; // 座標
		Vec3 m_scale = Vec3(1.1f, 0.1f, 1.0f); // サイズ

		Vec3 m_startPos; // スタート位置
		float m_endPosY; // 停止位置

		float m_speed = 1.0f;


	public:
		MoveFloorButton(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/** @brief 移動の開始位置と停止位置の設定
		*   @fn void SetUp
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void SetUp() {
			m_startPos  = m_position;
			m_endPosY = m_position.y + m_scale.y;
		}

		/** @brief プレイヤーがボタンに乗っているかどうか
		*   @fn bool PlayerOnButton(const Vec3& hitPoint)
		*   @param hitPoint プレイヤーとボタンの接触位置
		*   @return bool プレイヤーがボタンの上から接触しているとtrue
		*/
		bool PlayerOnButton(const Vec3& hitPoint) {
			float scaleYhelf = m_scale.y / 2;
			if (hitPoint.y > m_position.y + scaleYhelf) {
				return true;
			}
			return false;
		}

		/** @brief 接触判定が起こった時に呼び出される関数
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair 接触判定を起こしているオブジェクトペア
		*   @return 戻り値なし
		*/
		void OnCollisionEnter(const CollisionPair& Pair) override;
		/** @brief 接触し続けている時に呼び出される関数
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair 接触判定を起こしているオブジェクトペア
		*   @return 戻り値なし
		*/
		//void OnCollisionExcute(const CollisionPair& Pair) override;
		/** @brief 接触判定がなくなった時に呼び出される関数
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair 接触判定を起こしているオブジェクトペア
		*   @return 戻り値なし
		*/
		void OnCollisionExit(const CollisionPair& Pair) override;
	};
	//------------------------------------------------------------------------------------------------

	//------------------------ボタンで動く床--------------------------------------------------------
	class MoveFloor : public GameObject
	{
		// 稼働状態のステート
		enum class EMoveState {
			eTurnBack, // 戻る
			eStop,   // 停止
			eMove,   // 移動
		};

		enum EMoveState eMoveState = EMoveState::eStop; // 初期の移動状態は停止

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント
		std::shared_ptr<Action> m_actionComp; // アクションコンポーネント
		shared_ptr<SoundItem> m_kadouonn;

		Vec3 m_position; // 座標
		Vec3 m_scale; // サイズ
		Vec3 m_MoveDir; // 移動方向

		Vec3 m_startPos; // スタート位置
		Vec3 m_endPos;   // 停止位置

		float m_speed = 2.0f; // 移動スピード

		bool MoveSEPlay = false; // 移動時のSEを鳴らすかどうか

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
			m_MoveDir(movedir)
		{}

		void OnCreate();
		void OnUpdate();

		/** @brief 床の移動の処理
		*   @fn void FloorMovePattern()
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void FloorMovePattern();

		/** @brief 移動の開始位置と停止位置の設定
		*   @fn void SetUp()
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void SetUp() {
			m_startPos = m_position;
			m_endPos = m_position + (m_scale * 0.9f * m_MoveDir);
		}

		/** @brief 移動床のステート設定用関数
		*   @fn void FloorActive(const bool& active)
		*   @param active 床が動いているならtrue
		*   @return 戻り値なし
		* 　@details activeがtrueならeMove(移動)、falseならeTurnBack(戻る)
		*/
		void FloorActive(const bool& active) {
			if (active) {
				eMoveState = EMoveState::eMove;
			}
			else {
				eMoveState = EMoveState::eTurnBack;
			}
		}

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
		
		/** @brief プレイヤーがリスポーンした時に位置をリセットする関数(たまに止まってしまうため)
		*   @fn void ResetAll()
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void ResetAll();
	};
	//------------------------------------------------------------------------------------------------
}