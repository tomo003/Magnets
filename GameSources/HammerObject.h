/*!
* @file HammerObject.h
* @brief ハンマーオブジェクト
* @author 穴澤委也
* @details	ハンマーオブジェクト
*			ハンマーの前方エリアの判定
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class EState {
		eFalse = -1, // 無
		eN = 1, // Ｎ極
		eS = 2, // Ｓ極
		eMetal = 3 // 金属
	};

	/**
	* @brief ハンマーのエリア
	* @details ハンマーが振り下ろされる位置に生成
	*			プレイヤーがエリア内にいるときの判定を行う
	*/
	class HammerPressArea : public GameObject
	{
		// コンポーネント取得省略用
		shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント
		shared_ptr<CollisionObb> m_CollComp; // コリジョンコンポーネント

		Vec3 m_position;
		EState m_eMagPole;

		float m_AreaRightLimit; // エリアの右端
		float m_AreaLeftLimit; // エリアの左端

		// プレイヤーのポインタ
		shared_ptr<Player> m_ptrPlayerF; // Player1
		Vec3 m_PlayerFPos; // Player1の座標
		Vec3 m_PlayerFScaleHelf; // Player1のサイズの半分
		shared_ptr<Player2> m_ptrPlayerS; // Player2
		Vec3 m_PlayerSPos; // Player2の座標
		Vec3 m_PlayerSScaleHelf; // Player2のサイズの半分

	public:
		HammerPressArea(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position,
			const EState& mag
		) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(mag),
			m_AreaLeftLimit(m_position.x - 1.5f),
			m_AreaRightLimit(m_position.x + 1.5f)
		{}

		void OnCreate() override;

		bool AreaInPlayerF();
		bool AreaInPlayerS();
	};


	class HammerObject : public GameObject
	{
		// 動作関係のステート
		enum class HammerMoveState {
			Remove = -1, // 戻る
			Stop = 0, // 停止
			Antic = 1, // 予備動作(震える)
			Swing = 2, // 振り下ろし
		};
		HammerMoveState m_MoveState; // 現在のステート
		HammerMoveState m_lastMoveState; // 一個前のステート

		// コンポーネント取得省略用
		shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		shared_ptr<PNTBoneModelDraw> m_DrawComp; // ドローコンポーネント
		shared_ptr<CollisionObb> m_CollComp; // コリジョンコンポーネント

		Vec3 m_position; // 差分加算後の位置
		Vec3 m_CreatePos; // 生成時に入力された位置
		Vec3 m_posDiff = Vec3(0.0f, 4.625f, 4.625f); // 入力された位置と正規の位置の差分
		Vec3 m_Rotation; // 回転
		Vec3 m_Scale = Vec3(1.5f, 1.5f, 3.0f); // サイズ
		const float m_PivotLength = 3.625f; // 回転の中心(ピボット)を変える

		float m_SwingVal = 90.0f; // 回転角度
		float m_SwingSpeed = 5.0f; // 回転速度(角度に掛ける)

		EState m_eMagPole; // 磁極の状態

		float m_SwingStopTime = 1.0f; // 振り下ろし後の停止時間
		float m_ResetStopTime = 1.5f; //停止位置での停止時間
		float m_StopTime = 1.5f; // 停止時間

		float m_CurrentTime = 0.0f; // 現在停止時間(加算していく)

		// プレイヤーのポインタ
		shared_ptr<Player> m_ptrPlayerF; // Player1
		Vec3 m_PlayerFPos; // Player1の座標
		shared_ptr<Player2> m_ptrPlayerS; // Player2
		Vec3 m_PlayerSPos; // Player2の座標

		// エリアのポインタ
		shared_ptr<HammerPressArea> m_ptrPressArea; // つぶされる範囲のエリア
		shared_ptr<MagnetArea> m_MagArea; // 磁力エリア
		float m_MagAreaRadius = 3.5f;

		float m_TrembleRightX; // 振れ幅(右)
		float m_TrembleLeftX; // 振れ幅(左)
		int m_TrembleDir = 1; // 震えるときの方向(初期は正の値)
		int m_TrembleSpeed = 10; // 震えるときの速度

		shared_ptr<XAudio2Manager> m_ptrAudio; // SE再生用AudioManagerのポインタ
		bool isSEActive = false; // 振り下ろしのときのSEが再生中かどうか

	public:
		HammerObject(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position,
			const int& MagPole
		) :
			GameObject(stage),
			m_CreatePos(position),
			m_eMagPole(EState(MagPole)),
			m_MoveState(HammerMoveState::Stop), // 初期値は停止
			m_lastMoveState(HammerMoveState::Remove), // 初期値は戻る(停止時間を３秒にしたいため)
			m_TrembleRightX(m_position.x + 0.5f),
			m_TrembleLeftX(m_position.x - 0.5f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		/** @brief ハンマーのステートを渡す
		*   @param 引数なし
		*   @return 戻り値 m_MoveState　ハンマーの動作ステート
		*/
		HammerMoveState GetHammerMoveState() {
			return m_MoveState;
		}
		/** @brief ハンマーのステートをセット
		*   @param 引数 hms ハンマーの動作ステート
		*/
		void SetHammerMoveState(const HammerMoveState& hms) {
			m_MoveState = hms;
		}

		/** @brief 停止時間をセット
		*   @param 引数 time 秒
		*/
		void SetStopTime(const float time) {
			m_StopTime = time;
		}

		// @brief 現在の経過時間カウントをリセット
		void ResetCurrentTime() {
			m_CurrentTime = 0.0f;
		}

		/** @brief ハンマーの戻る動作
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void RemoveHammer();

		/** @brief ハンマーの停止動作
		*   @param 引数　lastState 一個前のステート
		*				　次のステートを設定するために使用
		*   @return 戻り値なし
		*/
		void StopHammer(const HammerMoveState& lastState);

		/** @brief ハンマーの予備動作
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void AnticHammer();
		/** @brief 予備動作用の振動
		*   @param time 時間
		*   @return 戻り値なし
		*/
		void AnticTremble(const float& time);

		/** @brief ハンマーの振り下ろす動作
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void SwingHammer();
		/** @brief 振り下ろし中にプレイヤーがいた時の処理
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void SwingingPlayerCheck();

		/** @brief 振り下ろし中に磁力エリアオブジェクトを補正する関数
		*   @param 引数なし
		*   @return 戻り値なし
		*/
		void MagAreaCorrection();
	};
}