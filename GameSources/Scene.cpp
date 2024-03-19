
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Scene::CreateResourses() {
		//�A�v���P�[�V�����I�u�W�F�N�g�ւ̎Q�Ƃ��擾����
		auto& app = App::GetApp();

		//�e�N�X�`���������Ă���t�H���_�̃p�X�𕶎���Ƃ��Ď擾����
		auto mediaPath = app->GetDataDirWString();//�umedia�v�p�X�𕶎���Ƃ��Ď擾����
		auto texturePath = mediaPath + L"Texture/";//�uTextures�v�t�H���_�̃p�X��A������

		wstring strTexture = texturePath + L"pcube01.png";
		app->RegisterTexture(L"Player_TX", strTexture);


		//���f���������Ă���t�H���_�̃p�X�𕶎���Ƃ��Ď擾����
		auto modelPath = mediaPath + L"Model/";//�uModel�v�t�H���_�̃p�X��A������

		auto staticPlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"01.bmf");
		App::GetApp()->RegisterResource(L"Player_MESH", staticPlayerMesh);
	}

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			CreateResourses();

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
