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

		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite;
		std::shared_ptr<ButtonSprite> m_ptrBbuttonSprite2;
		
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
