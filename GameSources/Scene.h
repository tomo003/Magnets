/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	enum class GameState {
		MainGame,
		GameOver,
		GameClear,
		Pause,
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		shared_ptr<EfkInterface> m_EfkInterface;
		int m_stageNum;
		int m_scene = 0;
		int m_score[5] = {0};
		shared_ptr<SoundItem> m_bgm;
		GameState m_GameState;
		int m_ResultNum;
		int m_PauseNum;

	public:

		void CreateResourses();

		//�e�N�X�`��
		void LoadTexture(const wstring& UseTextureName, const wstring& TextureDataName);
		//�ÓI���f��
		void LoadStaticModelMesh(const wstring& staticModelMeshName, const wstring& staticModelbmfName);
		//���I���f��
		void LoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName);
		//�{�[�����f��
		virtual void RegisterMultiMesh(const wstring& registerKey, const wstring& path, const wstring& fileName, bool boneUse);
		//�T�E���h
		void LoadSound(const wstring& soundName, const wstring& soundDataName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(), m_stageNum(1),m_GameState(GameState::MainGame),m_ResultNum(1) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		int GetSecen() {
			return m_scene;
		}
		int GetStageNum() const {
			return m_stageNum;
		}
		void SetStageNum(int s)
		{
			m_stageNum = s;
		}

		int GetResultNum() const {
			return m_ResultNum;
		}
		void SetResultNum(int s)
		{
			m_ResultNum = s;
		}
		int GetPauseNum() const {
			return m_PauseNum;
		}
		void SetPauseNum(int s)
		{
			m_PauseNum = s;
		}

		GameState GetGameState() const {
			return m_GameState;
		}

		void SetGameState(const GameState& gameState) {
			m_GameState = gameState;
		}

		void SetScore(const int i) {
			m_score[i - 1]++;
		}
		int GetScore(const int i) {
			return m_score[i - 1];
		}
		void ResetScore(const int i) {
			m_score[i - 1] = 0;
		}

	};
}

//end basecross
