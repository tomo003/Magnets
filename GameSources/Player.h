/*!
@file Player.h
@brief ƒvƒŒƒCƒ„[‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{

	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate();
		//void OnUpdate();
	};

}
//end basecross

