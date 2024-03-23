/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		const float ATTRACTION_CONSTANT = 100.0f; // 引力の定数
		const float REPEL_CONSTANT = 200.0f;   // 反発の定数
		const float MAX_SPEED = 40.0f;         // 最大速度

		//InputHandler<Player> m_InputHandler;

		float speed;
		Vec2 Velocity;

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
			speed(5),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();

		void MovePlayer();
		void JumpPlayer();

		void AnimationPlayer(eMotion Motion);

		//void ApplyAttraction();
	};

}
//end basecross

