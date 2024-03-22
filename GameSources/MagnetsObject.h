/*!
@file MagnetsObject.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse, // 無
			eN, // Ｎ極
			eS // Ｓ極
		};

	private:
		enum EState m_eMagPole;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント
 
	public:
		MagnetsObject(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate();
		void OnUpdate();
	};

}
//end basecross

