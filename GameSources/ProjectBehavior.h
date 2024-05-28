/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	template<typename T>
	struct InputHandler {
		void PushHandler(const shared_ptr<T>& Obj) {
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
			}
		}
	};
}

//end basecross

