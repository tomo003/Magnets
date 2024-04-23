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
		//enum class EState {
		//	eFalse = -1, // ��
		//	eN = 1, // �m��
		//	eS = 2 // �r��
		//};
		float m_time = 2.0f;

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
		bool playerBPush = false;
		bool player2BPush = false;
		bool playerReady = false;
		bool player2Ready = false;
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

		void CreateObjGroup();
	};


}
//end basecross
