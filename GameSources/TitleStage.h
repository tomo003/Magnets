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

	public:
		TitleStage() :
			Stage()
		{
		}
		virtual ~TitleStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		//virtual void OnDestroy()override;

		
	};
}