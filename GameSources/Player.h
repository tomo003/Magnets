/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		const float ATTRACTION_CONSTANT = 10.0f; // 引力の定数
		const float REPEL_CONSTANT = 20.0f;   // 反発の定数
		const float MAX_SPEED = 4.0f;         // 最大速度

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2 // Ｓ極
		};

	private:
		enum EState m_eMagPole = EState::eN;

		float m_speed;
		Vec3 m_Velocity;
		float m_Acceleration; // 加速度(磁石は近いほど磁力が強いため)

		float m_playerMass = 1.0f;

		float jumpCount;
		int count;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // ドローコンポーネント

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
			m_speed(5),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		//void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();

		void AnimationPlayer(eMotion Motion);

		//void ApplyAttraction();
		void ApplyAttraction();
		void ApplyRepulsion();

		void limitSpeed();

		EState GetPlayerMagPole() {
			return m_eMagPole;
		}
	};

}
//end basecross

