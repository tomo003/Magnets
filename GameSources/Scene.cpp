/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	//�e�N�X�`���̓ǂݍ���
	void Scene::RoadTexture(const wstring& UseTextureName, const wstring& TextureDataName) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Texture\\" + TextureDataName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	// �ÓI���f���̓ǂݍ���
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,MeshResource::CreateStaticModelMesh(dataDir+ L"Model//",  staticModelbmfName + L".bmf")
		);
	}

	// �{�[�����f���̓ǂݍ���
	void Scene::RoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(boneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir + L"Model\\", boneModelbmfName + L".bmf"));

		App::GetApp()->RegisterResource(boneModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir + L"Model\\", boneModelbmfName + L".bmf")
		);
	}

	//�{�[�����f���̓ǂݍ��ݕ���
	void Scene::RegisterMultiMesh(const wstring& registerKey, const wstring& path, const wstring& fileName, bool boneUse)
	{
		shared_ptr<MultiMeshResource> modelMesh;
		if (boneUse)
		{
			modelMesh = MultiMeshResource::CreateBoneModelMultiMesh(path, fileName + L".bmf");
		}
		else
		{
			modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(path, fileName + L".bmf");
		}
		const auto& app = App::GetApp();
		app->RegisterResource(registerKey, modelMesh);
	}

	// �T�E���h�̓ǂݍ���
	void Scene::RoadSound(const wstring& soundName, const wstring& soundDataName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}



	void Scene::CreateResourses() {

		//�e�N�X�`��
		RoadTexture(L"Player01_TX", L"pcube01.png");
		RoadTexture(L"Player02_TX", L"pcube02.png");
		RoadTexture(L"Player03_TX", L"pcube03.png");
		RoadTexture(L"N_AREA_TX", L"MagnetAreaTypeN.png");
		RoadTexture(L"S_AREA_TX", L"MagnetAreaTypeS.png");
		RoadTexture(L"TYPEALL_TX", L"MagnetAreaTypeAll.png");

		RoadTexture(L"BPUSH", L"BPush.png");

		RoadStaticModelMesh(L"01", L"Player01_MESH");
		RoadStaticModelMesh(L"02", L"Player02_MESH");
		RoadStaticModelMesh(L"03", L"Player03_MESH");

		RoadBoneModel(L"Brack", L"PlayerMotionfbx_MESH", L"PlayerMotionfbx_MESH_TAN");
		RoadBoneModel(L"Brue", L"PlayerBlue_MESH", L"PlayerBlue_MESH_TAN");
		RoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN");

	}

	void Scene::OnCreate(){
		try {
			CreateResourses();

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(6.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
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
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToMagTestStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<PlayerMagTestStage>();
		}
	}

}
//end basecross
