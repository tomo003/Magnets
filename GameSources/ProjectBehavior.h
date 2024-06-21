/*!
@file ProjectBehavior.h
@brief �v���W�F�N�g��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�X�e�[�W�Z���N�g�V�[���ƃ|�[�Y���j���[�Ŏg�p����{�^���̏���
	template<typename T>
	struct InputHandler {
		void PushHandler(const shared_ptr<T>& Obj) {
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
			}
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushSTART();
				}
			}
		}
	};
}

//end basecross

