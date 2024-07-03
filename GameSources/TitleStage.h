/*!
@file TiteleStage.h
@brief �^�C�g�����
*/

#pragma once
#include "stdafx.h"
#include "ShutterSprite.h"

namespace basecross {
	class TitleStage : public Stage {
		
		bool stage = false;

		shared_ptr<SoundItem> m_bgm; // �T�E���h�A�C�e��

		void CreateViewLight();//�r���[�̍쐬
		void CreateTitleSprite();//�X�v���C�g�̍쐬
		//void PlayBGM();//BGM�̍쐬
		shared_ptr<ShutterSprite> m_sFade;
		shared_ptr<ShutterSprite> m_nFade;
		shared_ptr<Sprites> m_ptrSprite; // �t�F�[�h�p�X�v���C�g�̃|�C���^
		shared_ptr<PCTSpriteDraw> m_ptrSpriteDraw; // �t�F�[�h�p�X�v���C�g�̃h���[�R���|�[�l���g

		float m_CurrentTime = 0.0f; // �o�ߎ���
		float m_ToMovieTime = 10.0f; // ���[�r�[�X�e�[�W�܂ł̑J�ڎ���
		float m_FadeTime = 1.0f; // �t�F�[�h�ɂ����鎞��
		Col4 m_diffuseColor; // �t�F�[�h�p�X�v���C�g�̐F�ݒ�p
		bool isFadeOut = false; // �t�F�[�h�A�E�g���邩�ǂ����̃t���O

	public:
		TitleStage() :
			Stage(),
			m_diffuseColor(1.0f, 1.0f, 1.0f, 0.0f) // �t�F�[�h�p�X�v���C�g�͐������ɓ���
		{
		}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		
	};
}