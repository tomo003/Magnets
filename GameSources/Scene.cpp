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
		//LoadTexture(L"TYPEALL_TX", L"MagnetAreaE.png");
		//LoadTexture(L"TYPEALL_N_TX", L"MagnetAreaC.png");
		LoadTexture(L"TYPEALL_TX", L"MagnetAreaW.png");
		LoadTexture(L"TYPEALL_N_TX", L"MagnetAreaB.png");
		LoadTexture(L"TYPEALL_B_TX", L"MagnetAreaE.png");
		LoadTexture(L"GRAY_TX", L"GrayCircle.png");
		LoadTexture(L"BPUSH", L"PushB.png");
		LoadTexture(L"RBPUSH", L"PushRB.png");
		LoadTexture(L"READY", L"StandBy.png");
		LoadTexture(L"CLEAR", L"StageClear.png");
		LoadTexture(L"BACKTOTITLE", L"BackToTitle.png");
		LoadTexture(L"CHECKPOINT_TX", L"CheckPoint.png");

		LoadTexture(L"PAUSE_BACK", L"Pause.png");
		LoadTexture(L"MENU", L"Menu.png");
		LoadTexture(L"RETRY", L"Retry.png");

		LoadTexture(L"BACKGROUND1", L"BackA.png");
		LoadTexture(L"BACKGROUND2", L"BackB.png");
		LoadTexture(L"BACKGROUND3", L"BackC.png");
		LoadTexture(L"BACKGROUND4", L"BackD.png");
		LoadTexture(L"BACKGROUND5", L"BackE.png");
		LoadTexture(L"BACKGROUND6", L"BackF.png");

		LoadTexture(L"TITLE", L"title.png");

		LoadTexture(L"STAGE1", L"Stage1.png");
		LoadTexture(L"STAGE2", L"Stage2.png");
		LoadTexture(L"STAGE3", L"Stage3.png");
		LoadTexture(L"STAGE4", L"Stage4.png");
		LoadTexture(L"STAGE5", L"Stage5.png");
		LoadTexture(L"STAGE6", L"Stage6.png");

		LoadTexture(L"STAGE1UI", L"Stage1UI.png");
		LoadTexture(L"STAGE2UI", L"Stage2UI.png");
		LoadTexture(L"STAGE3UI", L"Stage3UI.png");
		LoadTexture(L"STAGE4UI", L"Stage4UI.png");
		LoadTexture(L"STAGE5UI", L"Stage5UI.png");
		LoadTexture(L"STAGE6UI", L"Stage6UI.png");
		LoadTexture(L"STAGESELECT", L"StageSelect.png");
		LoadTexture(L"CURSOR", L"Cursor.png");

		LoadTexture(L"BACKTOSTAGESELECT", L"BackToStageSelect.png");
		LoadTexture(L"NEXTSTAGE", L"NextStage.png");

		LoadTexture(L"FADE_WHITE", L"Fade_White.png");
		LoadTexture(L"FADE_BLACK", L"Fade_Black.png");

		LoadTexture(L"MGNETN_TX", L"Tile_MGN.png");
		LoadTexture(L"MGNETS_TX", L"Tile_MGS.png");
		LoadTexture(L"BROCK_TX", L"Tile_Normal.png");
		LoadTexture(L"CONCRETE_TX", L"Tile_Concrete1.png");
		LoadTexture(L"CONCRETE2_TX", L"Ground2.png");
		LoadTexture(L"CONCRETE3_TX", L"Ground3.png");
		LoadTexture(L"GROUND_TX", L"Ground.png");
		LoadTexture(L"METAL_TX", L"Tile_Metal.png");
		LoadTexture(L"START_TX", L"Tile_Start.png");
		LoadTexture(L"SAVEPOINT_TX", L"Tile_SavePoint.png");
		LoadTexture(L"GOAL_TX", L"Tile_Goal.png");
		LoadTexture(L"MOVEFLOOR_TX", L"MoveFloor.png");

		LoadTexture(L"TENNSENNRED_TX", L"tennsennRed.png");
		LoadTexture(L"RED_TX", L"Red.png");
		LoadTexture(L"TENNSENNBLUE_TX", L"tennsennBlue.png");
		LoadTexture(L"BLUE_TX", L"Blue.png");
		LoadTexture(L"PURPLE_TX", L"Purple.png");
		LoadTexture(L"GREEN_TX", L"Green.png");
		LoadTexture(L"TENNSENNTRIANGLERED_TX", L"tennsennTriangleR.png");
		LoadTexture(L"TRIANGLERED_TX", L"TriangleR.png");
		LoadTexture(L"TENNSENNTRIANGLEBLUE_TX", L"tennsennTriangleB.png");
		LoadTexture(L"TRIANGLEBLUE_TX", L"TriangleB.png");

		LoadTexture(L"GUIDER_TX", L"GuideRight.png");
		LoadTexture(L"GUIDEL_TX", L"GuideLeft.png");

		LoadTexture(L"1P", L"1P.png");
		LoadTexture(L"2P", L"2P.png");
		LoadTexture(L"KEY", L"key.png");
		LoadTexture(L"NOKEY", L"NoKey.png");
		LoadTexture(L"ROCK", L"rock.png");
		LoadTexture(L"KEY7", L"key7.png");
		LoadTexture(L"KEY10", L"key10.png");
		LoadTexture(L"KEY13", L"key13.png");

		LoadStaticModelMesh(L"01", L"Player01_MESH");
		LoadStaticModelMesh(L"02", L"Player02_MESH");
		LoadStaticModelMesh(L"03", L"Player03_MESH");

		LoadBoneModel(L"Key", L"Key_MESH",L"Key_MESH_TAN");

		//Player1
		LoadBoneModel(L"Brack", L"PlayerBrack_MESH", L"PlayerBrack_MESH_TAN");//無極
		LoadBoneModel(L"Brue", L"PlayerBlue_MESH", L"PlayerBlue_MESH_TAN");//S極
		LoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN");//N極
		LoadBoneModel(L"Redanger", L"PlayerRedanger_MESH", L"PlayerRedanger_MESH_TAN");//N極

		//Player2
		LoadBoneModel(L"Brack", L"Player2Brack_MESH", L"Player2Brack_MESH_TAN");
		LoadBoneModel(L"Brue", L"Player2Blue_MESH", L"Player2Blue_MESH_TAN");
		LoadBoneModel(L"Blueanger", L"Player2Blueanger_MESH", L"Player2Blueanger_MESH_TAN");
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
		// 壊れる壁
		LoadBoneModel(L"BreakWall", L"BreakWall_MESH", L"BreakWall_MESH_TAN");

		//BGM
		LoadSound(L"TITLE_BGM",L"Title.wav");
		LoadSound(L"STANDBY_BGM",L"StandBy.wav");
		LoadSound(L"GAMESTAGE1_BGM",L"GameStage1.wav");
		LoadSound(L"GAMESTAGE2_BGM", L"GameStage2.wav");
		LoadSound(L"GAMESTAGE3_BGM", L"GameStage3.wav");
		LoadSound(L"GAMESTAGE4_BGM", L"GameStage4.wav");
		LoadSound(L"GAMESTAGE5_BGM", L"GameStage5.wav");
		LoadSound(L"GAMESTAGE6_BGM", L"GameStage6.wav");

		//効果音
		LoadSound(L"JUMP_SE", L"Jump.wav");
		LoadSound(L"UNION_SE", L"Union.wav");
		LoadSound(L"BUTTON_SE", L"Decition.wav");
		LoadSound(L"STOP_SE", L"Gachan.wav");
		LoadSound(L"KADOU_SE", L"Kadouonn.wav");
		LoadSound(L"SAVE_SE", L"Save.wav");
		LoadSound(L"GOAL_SE", L"Goal.wav");

	}

	void Scene::OnCreate(){
		try {
			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			Col.set(6.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToSelectStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnUpdate() {
		SceneBase::OnUpdate();
	}

	void Scene::OnDraw() {
		SceneBase::OnDraw();
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		const auto& audioPtr = App::GetApp()->GetXAudio2Manager();
		auto& app = App::GetApp();

		if (event->m_MsgStr == L"ToGameStage") {
			audioPtr->Stop(m_bgm);
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
			m_scene = 2;
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			m_bgm = audioPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 2.0f);
			ResetActiveStage<TitleStage>();
			m_scene = 0;
		}
		else if (event->m_MsgStr == L"ToStandbyStage") {
			ResetActiveStage<StandbyStage>();
			m_scene = 1;
		}
		else if (event->m_MsgStr == L"ToSelectStage") {
			audioPtr->Stop(m_bgm);
			ResetActiveStage<SelectStage>();
			m_scene = 3;
		}
		if (event->m_MsgStr == L"ToMagTestStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<PlayerMagTestStage>();
			m_scene = 10;
		}
	}

}
//end basecross
