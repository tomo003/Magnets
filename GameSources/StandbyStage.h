/*!
@file StandbyStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		float m_time = 2.0f;

		shared_ptr<SoundItem> m_bgm;
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
