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

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<BcPNTStaticModelDraw> m_ptrDraw; // ドローコンポーネント

	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			speed(5)
		{}

		void OnCreate();
		void OnUpdate();

		void MovePlayer();

		void ApplyAttraction();
	};

}
//end basecross

