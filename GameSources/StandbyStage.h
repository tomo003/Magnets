/*!
@file StandbyStage.h
@brief �X�^���o�C�X�e�[�W
@author �����I
@detail�@�ҋ@��ʂ̎���
*/

#pragma once
#include "stdafx.h"
#include "ShutterSprite.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		//����
		float m_time = 2.0f;
		float m_Totaltime = 0.0f;
		//�t�F�[�h
		shared_ptr<ShutterSprite> m_sFade;
		shared_ptr<ShutterSprite> m_nFade;
		//���y
		shared_ptr<SoundItem> m_bgm;
		shared_ptr<SoundItem> m_kadouonn;
		//�v���C���[
		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;
		//�{�^���X�v���C�g
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite;
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite2;
		//����
		std::shared_ptr<MagnetS> m_ptrMagObjS;
		std::shared_ptr<MagnetN> m_ptrMagObjN;

		//��������
		bool playerReady = false;
		bool player2Ready = false;
		bool playerPositionFixed = false;
		bool player2PositionFixed = false;
		bool stage = false;
		bool OperationSEPlay = false;

		const WORD BUTTON_START = XINPUT_GAMEPAD_START;//�X�^�[�g�{�^��
		const WORD BUTTON_BACK = XINPUT_GAMEPAD_BACK;//�o�b�N�{�^��

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		StandbyStage() :Stage(){}
		
		virtual ~StandbyStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

	};


}
//end basecross
