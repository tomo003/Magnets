
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

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


		//モデルが入っているフォルダのパスを文字列として取得する
		auto modelPath = mediaPath + L"Model/";//「Model」フォルダのパスを連結する

		auto staticNormalPlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"01.bmf");
		App::GetApp()->RegisterResource(L"Player01_MESH", staticNormalPlayerMesh);
		auto staticRedPlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"02.bmf");
		App::GetApp()->RegisterResource(L"Player02_MESH", staticRedPlayerMesh);
		auto staticBluePlayerMesh = MeshResource::CreateStaticModelMesh(modelPath, L"03.bmf");
		App::GetApp()->RegisterResource(L"Player03_MESH", staticBluePlayerMesh);
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
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
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
