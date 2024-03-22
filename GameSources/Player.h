/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		//InputHandler<Player> m_InputHandler;

		Vec3 speed;
		float jumpCount;

	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			speed(5),
			jumpCount(2)
		{}

		void OnCreate();
		void OnUpdate();

		void MovePlayer();
		void JumpPlayer();

	};

}
//end basecross

