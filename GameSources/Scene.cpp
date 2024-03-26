/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
<<<<<<< HEAD

	void Scene::CreateResourses() {
		//アプリケーションオブジェクトへの参照を取得する
		auto& app = App::GetApp();

		//テクスチャが入っているフォルダのパスを文字列として取得する
		auto mediaPath = app->GetDataDirWString();//「media」パスを文字列として取得する
		auto texturePath = mediaPath + L"Texture/";//「Textures」フォルダのパスを連結する

		wstring strTexture = texturePath + L"pcube01.png";
		app->RegisterTexture(L"Player01_TX", strTexture);
		strTexture = texturePath + L"pcube02.png";
		app->RegisterTexture(L"Player02_TX", strTexture);
		strTexture = texturePath + L"pcube03.png";
		app->RegisterTexture(L"Player03_TX", strTexture);
		strTexture = texturePath + L"MagnetAreaTypeN.png";
		app->RegisterTexture(L"N_AREA_TX", strTexture);
		strTexture = texturePath + L"MagnetAreaTypeS.png";
		app->RegisterTexture(L"S_AREA_TX", strTexture);
		strTexture = texturePath + L"MagnetAreaTypeAll.png";
		app->RegisterTexture(L"TYPEALL_TX", strTexture);


		//モデルが入っているフォルダのパスを文字列として取得する
		auto modelPath = mediaPath + L"Model/";//「Model」フォルダのパスを連結する

		auto staticNormalPlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"01.bmf");
		App::GetApp()->RegisterResource(L"Player01_MESH", staticNormalPlayerMesh);
		auto staticRedPlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"02.bmf");
		App::GetApp()->RegisterResource(L"Player02_MESH", staticRedPlayerMesh);
		auto staticBluePlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"03.bmf");
		App::GetApp()->RegisterResource(L"Player03_MESH", staticBluePlayerMesh);
	}

=======
>>>>>>> TitleStage
	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	//テクスチャの読み込み
	void Scene::RoadTexture(const wstring& UseTextureName, const wstring& TextureDataName) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Texture\\" + TextureDataName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	// 静的モデルの読み込み
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,MeshResource::CreateStaticModelMesh(dataDir+ L"Model//",  staticModelbmfName + L".bmf")
		);
	}

	// ボーンモデルの読み込み
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

	//ボーンモデルの読み込み複数
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

	// サウンドの読み込み
	void Scene::RoadSound(const wstring& soundName, const wstring& soundDataName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}



	void Scene::CreateResourses() {

		//テクスチャ
		RoadTexture(L"Player01_TX", L"pcube01.png");
		RoadTexture(L"Player02_TX", L"pcube02.png");
		RoadTexture(L"Player03_TX", L"pcube03.png");

		RoadTexture(L"BPUSH", L"BPush.png");

		RoadStaticModelMesh(L"01", L"Player01_MESH");
		RoadStaticModelMesh(L"02", L"Player02_MESH");
		RoadStaticModelMesh(L"03", L"Player03_MESH");

		RoadBoneModel(L"Motionfbx", L"PlayerMotionfbx_MESH", L"PlayerMotionfbx_MESH_TAN");
		RoadBoneModel(L"Blue", L"PlayerBlue_MESH", L"PlayerBlue_MESH_TAN");
		RoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN");

	}

	void Scene::OnCreate(){
		try {
			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			Col.set(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
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
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToMagTestStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<PlayerMagTestStage>();
		}
	}

}
//end basecross
