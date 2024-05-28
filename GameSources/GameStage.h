/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include"FlashSprite.h"
namespace basecross {
	class FlashSprite;

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;

		InputHandler<GameStage> m_InputHandler;

		shared_ptr<SoundItem> m_bgm;


		bool isCreateMaagnets = true;

		//�r���[�̍쐬
		void CreateViewLight();

		void CreateCsvObjects();

		float m_CSVHight = +42;

		vector<weak_ptr<FlashSprite>> m_SpVec;

		bool m_CntrolLock;

		void ChangeSelectMenu(int num);

		bool m_Clear;
		bool m_pushButton;
		bool m_Lock = false;
	public:


		//�\�z�Ɣj��
		GameStage() :Stage(),m_CntrolLock(false), m_SpVec(3) {}
		virtual ~GameStage() {}


		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM();
		void CreateAnimeSprite();
		void ClearResult();

		void OnPushB();
	};


}
//end basecross

