/*!
@file StageSelect.h
@brief �^�C�g�����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectScreenSprite;
	class SelectStage : public Stage {
		int m_score;

		bool stage = false;
		bool m_CntrolLock = false;
		bool m_Lock = false;
		vector<weak_ptr<SelectScreenSprite>> m_SpVec;
		shared_ptr<SoundItem> m_bgm; // �T�E���h�A�C�e��

		void CreateViewLight();//�r���[�̍쐬
		void CreateSelectSprite();//�X�v���C�g�̍쐬
		void CreateKeySprite();
		void CreateKeyLoad(const int scene ,const Vec3 pos);
		void CreateKeyRock();
		void ChangeSelect(int num);
		void CreateCursor();
		void CreateAnimeSprite();
		void PlayBGM();//BGM�̍쐬

	public:
		SelectStage() :
			Stage(), m_SpVec(6)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

	};
}

