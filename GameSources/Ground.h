/*!
@file Ground.h
@brief �n�ʂ�\���N���X���`����
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
