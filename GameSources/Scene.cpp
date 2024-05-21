/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	//テクスチャの読み込み
	void Scene::LoadTexture(const wstring& UseTextureName, const wstring& TextureDataName) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Texture\\" + TextureDataName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	// 静的モデルの読み込み
	void Scene::LoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,MeshResource::CreateStaticModelMesh(dataDir+ L"Model//",  staticModelbmfName + L".bmf")
		);
	}

	// ボーンモデルの読み込み
	void Scene::LoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName)
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
	void Scene::LoadSound(const wstring& soundName, const wstring& soundDataName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}



	void Scene::CreateResourses() {

		//テクスチャ
		LoadTexture(L"Player01_TX", L"pcube01.png");
		LoadTexture(L"Player02_TX", L"pcube02.png");
		LoadTexture(L"Player03_TX", L"pcube03.png");
		LoadTexture(L"N_AREA_TX", L"MagnetAreaTypeN.png");
		LoadTexture(L"S_AREA_TX", L"MagnetAreaTypeS.png");
		LoadTexture(L"TYPEALL_TX", L"MagnetAreaTypeAll.png");
		LoadTexture(L"GRAY_TX", L"GrayCircle.png");
		LoadTexture(L"BPUSH", L"PushB.png");
		LoadTexture(L"RBPUSH", L"PushRB.png");
		LoadTexture(L"READY", L"StandBy.png");
		LoadTexture(L"CLEAR", L"StageClear.png");
		LoadTexture(L"BACKTOTITLE", L"BackToTitle.png");

		LoadTexture(L"BACKGROUND", L"Back.png");
		LoadTexture(L"BACKGROUND1", L"Background_01.png");
		LoadTexture(L"BACKGROUND2", L"Background_02.png");
		LoadTexture(L"BACKGROUND3", L"Background_03.png");
		LoadTexture(L"BACKGROUND4", L"Background_04.png");
		LoadTexture(L"BACKGROUND5", L"Background_05.png");

		LoadTexture(L"TITLE", L"title.png");

		LoadTexture(L"FADE_WHITE", L"Fade_White.png");
		LoadTexture(L"FADE_BLACK", L"Fade_Black.png");

		LoadTexture(L"MGNETN_TX", L"Tile_MGN.png");
		LoadTexture(L"MGNETS_TX", L"Tile_MGS.png");
		LoadTexture(L"BROCK_TX", L"Tile_Normal.png");
		LoadTexture(L"CONCRETE_TX", L"Tile_Concrete.png");
		LoadTexture(L"METAL_TX", L"Tile_Metal.png");
		LoadTexture(L"START_TX", L"Tile_Start.png");
		LoadTexture(L"SAVEPOINT_TX", L"Tile_SavePoint.png");
		LoadTexture(L"GOAL_TX", L"Tile_Goal.png");
		LoadTexture(L"MOVEFLOOR_TX", L"MoveFloor.png");

		LoadTexture(L"TENNSENNRED_TX", L"tennsennRed.png");
		LoadTexture(L"RED_TX", L"Red.png");
		LoadTexture(L"TENNSENNBLUE_TX", L"tennsennBlue.png");
		LoadTexture(L"BLUE_TX", L"Blue.png");

		LoadTexture(L"1P", L"1P.png");
		LoadTexture(L"2P", L"2P.png");

		LoadStaticModelMesh(L"01", L"Player01_MESH");
		LoadStaticModelMesh(L"02", L"Player02_MESH");
		LoadStaticModelMesh(L"03", L"Player03_MESH");

		//Player1
		LoadBoneModel(L"Brack", L"PlayerBrack_MESH", L"PlayerBrack_MESH_TAN");//無極
		LoadBoneModel(L"Brue", L"PlayerBlue_MESH", L"PlayerBlue_MESH_TAN");//S極
		LoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN");//N極
		//Player2
		LoadBoneModel(L"Brack", L"Player2Brack_MESH", L"Player2Brack_MESH_TAN");
		LoadBoneModel(L"Brue", L"Player2Blue_MESH", L"Player2Blue_MESH_TAN");
		LoadBoneModel(L"Red", L"Player2Red_MESH", L"Player2Red_MESH_TAN");

		//ベルトコンベア
		wstring dataDir = App::GetApp()->GetDataDirWString();
		auto multiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(dataDir, L"m_Convayor.bmf");
		App::GetApp()->RegisterResource(L"CONVEYOR", multiModelMesh);
		auto multiModelMesh2 = MultiMeshResource::CreateBoneModelMultiMesh(dataDir, L"s_Convayor.bmf");
		App::GetApp()->RegisterResource(L"SIDE_CONVEYOR", multiModelMesh2);

		// 輪っか
		LoadStaticModelMesh(L"metalring04", L"RingObject_MESH");
		// 歯車
		LoadStaticModelMesh(L"GearObj", L"GearObject_MESH");

		//BGM
		LoadSound(L"TITLE_BGM",L"Title.wav");
		LoadSound(L"STANDBY_BGM",L"StandBy.wav");
		LoadSound(L"GAMESTAGE_BGM",L"GameStage.wav");
		//効果音
		LoadSound(L"JUMP_SE", L"Jump.wav");
		LoadSound(L"UNION_SE", L"Union.wav");
		LoadSound(L"BUTTON_SE", L"Decition.wav");

	}

	void Scene::OnCreate(){
		try {
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			Col.set(6.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnUpdate() {
		SceneBase::OnUpdate();
		m_EfkInterface->OnUpdate();
	}

	void Scene::OnDraw() {
		SceneBase::OnDraw();
		auto& camera = GetActiveStage()->GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(),camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
			m_scene = 2;
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
			m_scene = 0;
		}
		else if (event->m_MsgStr == L"ToStandbyStage") {
			ResetActiveStage<StandbyStage>();
			m_scene = 1;
		}
		if (event->m_MsgStr == L"ToMagTestStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<PlayerMagTestStage>();
			m_scene = 10;
		}
	}

}
//end basecross
