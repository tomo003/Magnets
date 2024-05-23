/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		shared_ptr<EfkInterface> m_EfkInterface;
		int m_stageNum;
		int m_scene = 0;

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
		Scene() :SceneBase(), m_stageNum(1) {}
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
		//�G�t�F�N�g�̃C���^�[�t�F�[�X�̎擾
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}

	};
}

//end basecross
