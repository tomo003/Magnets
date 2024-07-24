/*!
@file PlayerMagTestStage.h
@brief �v���C���[�̋@�\��I�u�W�F�N�g�̃e�X�g�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class PlayerMagTestStage : public Stage {
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3
		};

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		PlayerMagTestStage() :Stage() {}
		virtual ~PlayerMagTestStage() {}
		//������
		virtual void OnCreate()override;

		void CreateObjGroup();

		/**
		* @brief �w�i�����֐�
		* @param[in] texkey(�w�i�e�N�X�`���̖��O)
		* @return �߂�l�Ȃ�
		* @details for���[�v�ŕ����̔w�i��\��������
		*/
		void CreateBackGround(const wstring& texkey);
	};


}
//end basecross

