/*!
@file MagnetsObject.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetsObject : public GameObject
	{

	public:
		MagnetsObject(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate();
		//void OnUpdate();
	};

}
//end basecross

