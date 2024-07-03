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

	// ���[�r�[�X�e�[�W�ł̃R���g���[������
	template<typename T>
	struct InputHandler2 {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//A�{�^��
				if (cntlVec[0].wPressedButtons) {
					Obj->OnPushAny();
				}
				//�X�^�[�g�A�Z���N�g��������
				//if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
				//{
				//	Obj->OnReset();
				//}

			}
		}
	};
}

//end basecross

