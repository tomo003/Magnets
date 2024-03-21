/*!
@file Ground.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ground : public GameObject
	{
	public:
		Ground(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
	};
}
//end basecross
