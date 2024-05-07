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
	class GameStage : public Stage {

	private:
		CsvFile m_GameStageCsv;

		shared_ptr<SoundItem> m_bgm;

		bool isCreateMaagnets = true;

		//�r���[�̍쐬
		void CreateViewLight();

		void CreateCsvObjects();

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM();
	};


}
//end basecross

