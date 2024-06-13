/*!
* @file HammerObject.h
* @brief ハンマーオブジェクト
* @author 穴澤委也
* @details	ハンマーオブジェクト
*			ハンマーの前方エリアの判定
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class HammerObject : public GameObject
	{
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3
		};

	};
}