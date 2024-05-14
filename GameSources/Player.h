/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{

		const float ATTRACTION_CONSTANT = 150.0f; // 引力の定数
		const float REPEL_CONSTANT = 200.0f;   // 反発の定数
		const float MAX_SPEED = 10.0f;         // 最大速度

		// プレイヤーのジャンプに使用するボタン
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2 // Ｓ極
		};

	private:
		enum EState m_eMagPole = EState::eN; // 磁極の状態

		Vec3 m_pos;
		float m_speed;
		int m_attribute;
		Vec3 m_Velocity;
		float m_Acceleration; // 加速度(磁石は近いほど磁力が強いため)

		Vec3 m_direction;
		float m_distance = 1000.0f;
		float m_distanceTemp;
		Vec3 m_force;

		Vec3 m_nearMagnetPos;//近い磁石オブジェクトの位置

		const Vec3 m_gravityVelocity = Vec3(0.0f, 8.0f, 0.0f);
		const Vec3 m_gravity = Vec3(0, -9.8f, 0);

		float m_playerMass = 1.0f;

		float jumpCount;
		int count;
		bool isGround;

		bool isEffect = true;

		float m_RespawnPoint;//リスポーンする位置

		wstring m_magDirLR;
		wstring m_magDirUD;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // ドローコンポーネント
		std::shared_ptr<Gravity> m_gravityComp;

		bool isCollRing = false; // リングと接触しているか(初期値はfalse)
		bool isCollGoal = false;

		enum eMotion {
			RIGHT,
			LEFT,
			FRONT,
			BACK,
		};
		vector<wstring> m_motionKey = {
			L"RIGHT",
			L"LEFT",
			L"FRONT",
			L"BACK",
		};
		// 現在のフレームのモーションを保持
		eMotion m_currentMotion;
		// 前フレームのモーションを保持
		eMotion m_pastMotion;


	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(5.0f),
			m_attribute(1),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();
		void JumpCountReset() {
			jumpCount = 2;
		}
		void GoalPlayer();
		void SetRespawnPoint(shared_ptr<GameObject>& Other);
		float GetRespawnPoint()const {
			return m_RespawnPoint;
		}
		void RespawnPlayer(float respawnPoint);


		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void AnimationPlayer(eMotion Motion);

		void ApplyAttraction(shared_ptr<GameObject>& Other); // プレイヤーに引力を適用
		void ApplyRepulsion(shared_ptr<GameObject>& Other);  // プレイヤーに斥力を適用

		void PlayerApplyAttraction();
		void PlayerApplyRepulsion();

		void ApplyForcePlayer();

		void limitSpeed();

		// プレイヤーの磁極を他クラスで取得する用の関数
		EState GetPlayerMagPole() {
			return m_eMagPole;
		}

		// 近い磁石が自分から見て4方向のどこにいるか設定
		void SetMsgnetsDirection(const Vec3& magPos) {
			if (m_pos.y < magPos.y) {
				m_magDirUD = L"UP";
			}
			if (m_pos.y > magPos.y) {
				m_magDirUD = L"DOWN";
			}
			if (m_pos.x < magPos.x) {
				m_magDirLR = L"RIGHT";
			}
			if (m_pos.x > magPos.x) {
				m_magDirLR = L"LEFT";
			}
		}
		// ↑のを取得
		pair<wstring,wstring> GetMsgnetsDirection() {
			return make_pair(m_magDirLR, m_magDirUD);
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

	};

}
//end basecross

