/*!
@file Player.h
@brief ƒvƒŒƒCƒ„[‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		//InputHandler<Player> m_InputHandler;

		Vec3 speed;
	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			speed(5)
		{}

		void OnCreate();
		void OnUpdate();

		void MovePlayer();
	};

}
//end basecross

