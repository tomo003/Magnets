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

		//�X�v���C�gWeak_ptr�̔z��
		vector<weak_ptr<FlashSprite>> m_SpVec;
		std::shared_ptr<FlashSprite> m_Flash;
		vector<weak_ptr<FlashSprite>> m_PsVec;

		//�r���[�̍쐬
		void CreateViewLight();

		void CreateCsvObjects();

		float m_CSVHeight = +42;

		int m_score = 0;
		int m_previousScore = -1;

		bool m_CntrolLock;

		void Menu();
		void ChangeSelectMenu(int num);
		void ChangeSelectPauseMenu(int num);


		bool m_Clear;
		bool m_pushButton;
		bool m_Lock = false;

		shared_ptr<GameObject> m_ptrPlayer1;
		shared_ptr<GameObject> m_ptrPlayer2;

	public:


		//�\�z�Ɣj��
		GameStage() :Stage(),m_CntrolLock(false), m_SpVec(3),m_PsVec(3) {}
		virtual ~GameStage() {}


		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void CreateObjGroup();
		void PlayBGM(wstring sound);
		void CreateAnimeSprite();
		void ClearResult();
		void CreateKeyLoad(const int scene, const Vec3 pos);

		/**
		* @brief �w�i�����֐�
		* @param[in] texkey(�w�i�e�N�X�`���̖��O)
		* @return �߂�l�Ȃ�
		* @details for���[�v�ŕ����̔w�i��\��������
		*/
		void CreateBackGround(const wstring& texkey);
		void CreatePauseSprite();
		void OnPushSTART();
		void OnPushB();

		/*!
		@brief �R���W������ON/OFF����֐�
		@param �����Ȃ�
		@return �߂�l�Ȃ�
		*/
		void CollisionSwitch();

		/*!
		@brief �R���W������ON/OFF����֐�(�O���[�v)
		@param wstring groupStr �O���[�v��
		@return �߂�l�Ȃ�
		*/
		void GroupCollisionSwitch(wstring groupStr);
	};

}
//end basecross

