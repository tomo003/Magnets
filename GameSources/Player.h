/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{

		//const float ATTRACTION_CONSTANT = 150.0f; // 引力の定数
		//const float REPEL_CONSTANT = 200.0f;   // 反発の定数
		//const float MAX_SPEED = 10.0f;         // 最大速度
		const float ATTRACTION_CONSTANT = 150.0f; // 引力の定数
		const float REPEL_CONSTANT = 400.0f;   // 反発の定数
		const float MAX_SPEED = 20.0f;         // 最大速度
		const float LIMIT_MAX_SPEED = 5.0f;    //プレイヤー同士が川なっているときの最大速度

		// プレイヤーのジャンプに使用するボタン
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

		enum class magneticState {
			emNone = -1, // くっついてない
			emPlayer = 0, // Player
			emMagnet = 1, // MagnetN,S
			emRing = 2, // ring
			emGear = 3, // Gear
			emMetal = 4 // Metal,MoveMetal
		};

	private:
		EState m_eMagPole = EState::eN; // 磁極の状態
		magneticState m_emState = magneticState::emNone;

		Vec3 m_Scale = Vec3(1.0f);
		Vec3 m_pos;
		float m_speed;
		float m_speedReset;
		int m_attribute;
		Vec3 m_Velocity;
		float m_Acceleration; // 加速度(磁石は近いほど磁力が強いため)

		Vec3 m_direction;
		float m_distance = 1000.0f;
		float m_distanceTemp;
		Vec3 m_force;

		//プレイヤー同士が離れると行動制限がかかる距離
		float m_limit = 35;
		bool isRightLimit = false;
		bool isLeftLimit = false;

		Vec3 m_nearMagnetPos;//近い磁石オブジェクトの位置

		const Vec3 m_gravityVelocity = Vec3(0.0f, 8.0f, 0.0f);
		const Vec3 m_gravity = Vec3(0, -9.8f, 0);

		float m_playerMass = 100.0f;

		Vec3 m_objPos = Vec3(0);

		float jumpCount;
		int count;
		bool isJump = true;
		bool isInertia = false; // ベルトコンベア系
		Vec3 m_inertia;

		bool isPlayerContact;

		bool isEffect = true;
		bool isGround; // 着地しているかの判定
		bool isRepulsion = false; // 反発してるときtrue
		bool isAttration = false; // 吸引されてるときtrue
		bool isBelt = false;

		bool isContactFirst = true;

		Vec3 m_RespawnPoint;//リスポーンする位置

		Vec3 m_magDirUD;
		Vec3 m_magDirLR;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // ドローコンポーネント
		std::shared_ptr<CollisionObb> m_ptrColl; // ドローコンポーネント
		std::shared_ptr<Gravity> m_gravityComp;

		std::shared_ptr<PlayerBanner> m_playerBanner;

		bool isGearFloor = false;
		bool isStop = false;

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
			m_speedReset(5.0f),
			m_attribute(1),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		void OnUpdate2();

		void MovePlayer(); // プレイヤーの移動
		void JumpPlayer(); // プレイヤーのジャンプ(デバッグ用)
		void JumpCountReset() { // ジャンプ回数リセット用
			jumpCount = 2;
		}
		void GoalPlayer();
		void SetRespawnPoint(shared_ptr<GameObject>& Other);
		void SetRespawnPoint(Vec3 RepawnPoint);
		Vec3 GetRespawnPoint()const {
			return m_RespawnPoint;
		}
		void RespawnPlayer();

		void PlayerLimit();
		void PlayerBannerPosition(Vec3 position);

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void AnimationPlayer(eMotion Motion);

		void ApplyAttration(shared_ptr<GameObject>& Other); // プレイヤーに引力を適用
		void ApplyRepulsion(shared_ptr<GameObject>& Other);  // プレイヤーに斥力を適用

		void PlayerApplyAttration();
		void PlayerApplyRepulsion();

		void ApplyForcePlayer();

		void limitSpeed();

		// プレイヤーの磁極を他クラスで取得する用の関数
		EState GetPlayerMagPole() {
			return m_eMagPole;
		}
		void SetPlayerMagPole(int i);

		// 近い磁石が自分から見て4方向のどこにいるか設定
		void SetMsgnetsDirection(const Vec3& magPos) {
			if (m_pos.y < magPos.y - 1.0f) {
				m_magDirUD = UP_VEC;
			}
			if (m_pos.y > magPos.y + 1.0f) {
				m_magDirUD = DOWN_VEC;
			}
			if (m_pos.x < magPos.x - 1.0f) {
				m_magDirLR = RIGHT_VEC;
			}
			if (m_pos.x > magPos.x + 1.0f) {
				m_magDirLR = LEFT_VEC;
			}
		}

		// 角にくっつかないように少し下にずらす
		void ShiftDown(const Vec3& objPos) {
			if (m_pos.y < objPos.y - 0.9f &&
				((m_pos.x < objPos.x - 0.9f) || (m_pos.x > objPos.x + 0.9f))) {
				m_pos.y -= 0.1f;
				m_ptrTrans->SetPosition(m_pos);
			}
		}

		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void LandingJadge(shared_ptr<GameObject>& Other) {
			auto ptrOtherObjTrans = Other->GetComponent<Transform>();
			Vec3 OtherObjPos = ptrOtherObjTrans->GetPosition();
			float OtherObjScaleHalfY = ptrOtherObjTrans->GetScale().y / 2;
			float playerScaleHalfY = m_ptrTrans->GetScale().y / 2;
			float ScaleYDiff = OtherObjScaleHalfY + playerScaleHalfY;
			float PosYDiff = fabs(OtherObjPos.y - m_pos.y);

			if (PosYDiff >= ScaleYDiff) {
				isGround = true;
			}
		}

		/**
		* @brief スピードをゼロにする関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void ZEROSpeed() {
			m_speed = 0.0f;
		}
		/**
		* @brief スピードをリセットする関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void RESETSpeed() {
			m_speed = m_speedReset;
		}

		/**
		* @brief 反発状態かどうかを他クラスに渡すための関数
		* @param 引数なし
		* @return bool 反発状態ならtrue
		*/
		bool IsRepulState() {
			return isRepulsion;
		}
		/**
		* @brief 反発状態を設定する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void SetRepulState(bool state) {
			isRepulsion = state;
		}
		/**
		* @brief 吸引状態かどうかを他クラスに渡すための関数
		* @param 引数なし
		* @return bool 吸引状態ならtrue
		*/
		bool IsAttrationState() {
			return isAttration;
		}
		/**
		* @brief 吸引状態を設定する関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void SetAttrationState(bool state) {
			isAttration = state;
		}

		/**
		* @brief プレイヤー死亡時に呼び出す関数
		* @param 引数なし
		* @return 戻り値なし
		* @details この関数内でRespawnPlayerを呼び出す
		*/
		void PlayerDeath();
		void PlayerDeathEffect();


		// ゴール判定
		bool IsGoal() {
			return isStop;
		}

		// GearFloorに接触しているかどうかを渡す関数
		bool IsGearFloor() {
			return isGearFloor;
		}
	};

}
//end basecross

