/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class PlayerMagTestStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		PlayerMagTestStage() :Stage() {}
		virtual ~PlayerMagTestStage() {}
		//������
		virtual void OnCreate()override;

		void CreateObjGroup();
	};


}
//end basecross

