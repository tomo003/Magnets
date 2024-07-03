/*!
@file MovieStage.h
@brief �^�C�g�����[�r�[�𗬂�

*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleMovieStage : public MovieStage {
		//���̓n���h���[
		InputHandler2<TitleMovieStage> m_InputHandler;

		shared_ptr<Sprites> m_ptrSprite; // �t�F�[�h�p�X�v���C�g�̃|�C���^
		shared_ptr<PCTSpriteDraw> m_ptrSpriteDraw; // �t�F�[�h�p�X�v���C�g�̃h���[�R���|�[�l���g

		float m_FadeTime = 1.0f; // �t�F�[�h�A�E�g�ɂ����鎞��
		Col4 m_diffuseColor; // �t�F�[�h�X�v���C�g�̐F�ێ��p
		bool isFadeOut = false; // �t�F�[�h�A�E�g���邩�ǂ����̃t���O

	public:
		//�\�z�Ɣj��
		TitleMovieStage() :
			MovieStage(),
			m_diffuseColor(1.0f, 1.0f, 1.0f, 0.0f)
		{
		}
		virtual ~TitleMovieStage() {}
		//������
		void CreateViewLight();
		void OnCreate()override;
		void OnUpdate() override;
		//�{�^��
		void OnPushAny();
		//void OnReset();
	};


}
//end basecross
