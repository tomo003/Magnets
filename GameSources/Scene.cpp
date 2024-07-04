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
	void Scene::RegisterMultiMesh(const wstring& registerKey, const wstring& fileName, bool boneUse)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		shared_ptr<MultiMeshResource> modelMesh;
		if (boneUse)
		{
			modelMesh = MultiMeshResource::CreateBoneModelMultiMesh(dataDir + L"Model\\", fileName + L".bmf");
		}
		else
		{
			modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(dataDir + L"Model\\", fileName + L".bmf");
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
		LoadTexture(L"Player01_TX", L"pcube01.png"); // Player用テクスチャ
		LoadTexture(L"Player02_TX", L"pcube02.png");
		LoadTexture(L"Player03_TX", L"pcube03.png");
		LoadTexture(L"TYPEALL_TX", L"MagnetAreaW.png"); // 磁力エリア用テクスチャ
		LoadTexture(L"TYPEALL_N_TX", L"MagnetAreaB.png"); // 磁力エリア用テクスチャ
		LoadTexture(L"TYPEALL_B_TX", L"MagnetAreaE.png"); // 磁力エリア用テクスチャ
		LoadTexture(L"BPUSH", L"PushB.png"); // Bボタン用
		LoadTexture(L"RBPUSH", L"PushRB.png"); // RBボタン用
		LoadTexture(L"READY", L"StandBy.png"); // STANDBY(文字)
		LoadTexture(L"CLEAR", L"StageClear.png"); // ステージクリア
		LoadTexture(L"BACKTOTITLE", L"BackToTitle.png");//タイトルに戻る文字UI
		LoadTexture(L"CHECKPOINT_TX", L"CheckPoint.png"); // 中間地点

		LoadTexture(L"PAUSE_BACK", L"Pause.png");//ポーズメニューのウィンドウ背景
		LoadTexture(L"MENU", L"Menu.png");//ポーズメニューで表示されるメニュー文字UI
		LoadTexture(L"RETRY", L"Retry.png");//ポーズメニューで表示されるリトライ文字UI

		LoadTexture(L"BACKGROUND1", L"BackA.png");//ステージ1の背景
		LoadTexture(L"BACKGROUND2", L"BackB.png");//ステージ2の背景
		LoadTexture(L"BACKGROUND3", L"BackC.png");//ステージ3の背景
		LoadTexture(L"BACKGROUND4", L"BackD.png");//ステージ4の背景
		LoadTexture(L"BACKGROUND5", L"BackE.png");//ステージ5の背景
		LoadTexture(L"BACKGROUND6", L"BackF.png");//ステージ6の背景

		LoadTexture(L"TITLE", L"title.png");//タイトルロゴ

		LoadTexture(L"STAGE1", L"Stage1.png");//ステージセレクトシーンに使う「ステージ1～6」のスクショスプライト
		LoadTexture(L"STAGE2", L"Stage2.png");
		LoadTexture(L"STAGE3", L"Stage3.png");
		LoadTexture(L"STAGE4", L"Stage4.png");
		LoadTexture(L"STAGE5", L"Stage5.png");
		LoadTexture(L"STAGE6", L"Stage6.png");

		LoadTexture(L"EASY", L"Easy.png");//難易度表示のスプライト
		LoadTexture(L"NORMAL", L"Normal.png");
		LoadTexture(L"HARD", L"Hard.png");


		LoadTexture(L"STAGE1UI", L"Stage1UI.png");//ステージセレクトシーンに使う「ステージ1～6」までの文字UI
		LoadTexture(L"STAGE2UI", L"Stage2UI.png");
		LoadTexture(L"STAGE3UI", L"Stage3UI.png");
		LoadTexture(L"STAGE4UI", L"Stage4UI.png");
		LoadTexture(L"STAGE5UI", L"Stage5UI.png");
		LoadTexture(L"STAGE6UI", L"Stage6UI.png");
		LoadTexture(L"STAGESELECT", L"StageSelect.png");//ステージセレクトシーンに使う左上のステージセレクト文字
		LoadTexture(L"CURSOR", L"Cursor.png");//ステージセレクトシーンに使う黄色カーソルスプライト

		LoadTexture(L"BACKTOSTAGESELECT", L"BackToStageSelect.png");//ステージセレクトシーンに戻る文字UI
		LoadTexture(L"NEXTSTAGE", L"NextStage.png");//次のステージへ文字UI

		LoadTexture(L"FADE_WHITE", L"Fade_White.png"); // フェード用
		LoadTexture(L"FADE_BLACK", L"Fade_Black.png"); // フェード用
		LoadTexture(L"SFADE", L"SFade.png");//シーン切り替えでつかうシャッターみたいに閉じる用のスプライト（S極、N極）
		LoadTexture(L"NFADE", L"NFade.png");

		LoadTexture(L"MGNETN_TX", L"Tile_MGN.png"); // N極ブロック
		LoadTexture(L"MGNETS_TX", L"Tile_MGS.png"); // S極ブロック
		LoadTexture(L"GROUND_TX", L"Ground.png"); // 床オブジェクト
		LoadTexture(L"CONCRETE2_TX", L"Ground2.png"); // 床オブジェクト(2x2)
		LoadTexture(L"CONCRETE3_TX", L"Ground3.png"); // 床オブジェクト(3x3)
		LoadTexture(L"METAL_TX", L"Tile_Metal.png"); // 金属オブジェクト
		LoadTexture(L"MOVEFLOOR_TX", L"MoveFloor.png"); // 移動床用

		LoadTexture(L"TENNSENNRED_TX", L"tennsennRed.png"); // ゴール通過チェック用(Player1用点線)
		LoadTexture(L"RED_TX", L"Red.png"); // ゴール通過チェック用(Player1用)
		LoadTexture(L"TENNSENNBLUE_TX", L"tennsennBlue.png"); // ゴール通過チェック用(Player2用点線)
		LoadTexture(L"BLUE_TX", L"Blue.png"); // ゴール通過チェック用(Player2用)
		LoadTexture(L"PURPLE_TX", L"Purple.png"); // 中間地点の輪っか用
		LoadTexture(L"GREEN_TX", L"Green.png"); // 中間地点の輪っか用
		LoadTexture(L"TENNSENNTRIANGLERED_TX", L"tennsennTriangleR.png"); // 中間地点通過チェック用(Player1用点線)
		LoadTexture(L"TRIANGLERED_TX", L"TriangleR.png"); // 中間地点通過チェック用(Player1用)
		LoadTexture(L"TENNSENNTRIANGLEBLUE_TX", L"tennsennTriangleB.png"); // 中間地点通過チェック用(Player2用点線)
		LoadTexture(L"TRIANGLEBLUE_TX", L"TriangleB.png"); // 中間地点通過チェック用(Player2用)

		LoadTexture(L"1P", L"1P.png"); // バナー(Player1用)
		LoadTexture(L"2P", L"2P.png"); // バナー(Player2用)
		LoadTexture(L"KEY", L"key.png"); // 鍵
		LoadTexture(L"NOKEY", L"NoKey.png"); // 鍵(空欄)
		LoadTexture(L"ROCK", L"rock.png"); // 施錠
		LoadTexture(L"KEY7", L"key7.png"); // 鍵7個必要
		LoadTexture(L"KEY10", L"key10.png"); // 鍵10個必要
		LoadTexture(L"KEY13", L"key13.png"); // 鍵13個必要

		LoadTexture(L"DEATHEFFECT", L"DeathEffect.png");

		//ガイドの画像
		LoadTexture(L"GUIDEREDUP_TX", L"GuideRedUp.png"); // 上向き(Player1用)
		LoadTexture(L"GUIDEREDDOWM_TX", L"GuideRedDown.png"); // 下向き(Player1用)
		LoadTexture(L"GUIDEREDCENTER_TX", L"GuideRedCenter.png"); // 横向き(Player1用)
		LoadTexture(L"GUIDEBLUEUP_TX", L"GuideBlueUp.png"); // 上向き(Player2用)
		LoadTexture(L"GUIDEBLUEDOWM_TX", L"GuideBlueDown.png"); // 下向き(Player2用)
		LoadTexture(L"GUIDEBLUECENTER_TX", L"GuideBlueCenter.png"); // 横向き(Player2用)

		// 鍵オブジェクト
		LoadBoneModel(L"Key", L"Key_MESH",L"Key_MESH_TAN");

		//Player1
		LoadBoneModel(L"Brack", L"PlayerBrack_MESH", L"PlayerBrack_MESH_TAN"); //無極
		LoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN"); //N極
		LoadBoneModel(L"Redanger", L"PlayerRedanger_MESH", L"PlayerRedanger_MESH_TAN"); //N極(怒り顔)
		LoadBoneModel(L"blacksmile", L"PlayerBrackSmile_MESH", L"PlayerBrackSmile_MESH_TAN"); //無極(にっこり)
		LoadBoneModel(L"Redsmile", L"PlayerRedSmile_MESH", L"PlayerRedSmile_MESH_TAN"); //N極(にっこり)

		//Player2
		LoadBoneModel(L"Brack", L"Player2Brack_MESH", L"Player2Brack_MESH_TAN"); //無極
		LoadBoneModel(L"Brue", L"Player2Blue_MESH", L"Player2Blue_MESH_TAN"); //S極
		LoadBoneModel(L"Blueanger", L"Player2Blueanger_MESH", L"Player2Blueanger_MESH_TAN");// S極(怒り顔)
		LoadBoneModel(L"blacksmile", L"Player2BrackSmile_MESH", L"Player2BrackSmile_MESH_TAN");// 無極(にっこり)
		LoadBoneModel(L"Greensmile", L"Player2BlueSmile_MESH", L"Player2BlueSmile_MESH_TAN"); // S極(にっこり)

		//ベルトコンベア
		LoadTexture(L"GUIDER_TX", L"GuideRight.png"); // ベルトコンベアの右向き矢印
		LoadTexture(L"GUIDEL_TX", L"GuideLeft.png"); // ベルトコンベアの左向き矢印
		RegisterMultiMesh(L"CONVEYOR", L"m_Convayor", true); // ベルトコンベア
		RegisterMultiMesh(L"SIDE_CONVEYOR", L"s_Convayor", true); // ベルトコンベア(端)

		// 輪っか
		LoadStaticModelMesh(L"metalring04", L"RingObject_MESH");
		// 歯車
		LoadStaticModelMesh(L"GearObj", L"GearObject_MESH");
		// 壊れる壁
		LoadBoneModel(L"BreakWall", L"BreakWall_MESH", L"BreakWall_MESH_TAN");
		LoadTexture(L"BREAK_TX", L"BreakWallTex.png");
		// ハンマー(赤&青&黒)
		LoadBoneModel(L"Hammer Red", L"Hammer_Red_MESH", L"Hammer_Red_MESHTAN");
		LoadBoneModel(L"Hammer Green", L"Hammer_Blue_MESH", L"Hammer_Blue_MESHTAN");
		LoadBoneModel(L"Hammer Black", L"Hammer_Black_MESH", L"Hammer_Black_MESHTAN");
		// ハンマーエリア(Ｎ＆Ｓ＆無)
		LoadTexture(L"REDAREA_TX", L"HummerArea_Red.png");
		LoadTexture(L"BULEAREA_TX", L"HummerArea_Bule.png");
		LoadTexture(L"WHITEAREA_TX", L"HummerArea_White.png");

		//BGM
		LoadSound(L"TITLE_BGM",L"Title.wav");//タイトルシーン
		LoadSound(L"STANDBY_BGM",L"StandBy.wav");//準備完了シーン
		LoadSound(L"GAMESTAGE1_BGM", L"GameStage1.wav");//ステージ1~6
		LoadSound(L"GAMESTAGE2_BGM", L"GameStage2.wav");
		LoadSound(L"GAMESTAGE3_BGM", L"GameStage3.wav");
		LoadSound(L"GAMESTAGE4_BGM", L"GameStage4.wav");
		LoadSound(L"GAMESTAGE5_BGM", L"GameStage5.wav");
		LoadSound(L"GAMESTAGE6_BGM", L"GameStage6.wav");

		//効果音
		LoadSound(L"JUMP_SE", L"Jump.wav");//ジャンプ
		LoadSound(L"UNION_SE", L"Union.wav");//磁石でくっついたとき
		LoadSound(L"BUTTON_SE", L"Decition.wav");//ボタン押したときの決定音
		LoadSound(L"STOP_SE", L"Gachan.wav");//スタート地点に運ばれてきて停止したときの音
		LoadSound(L"OPERATION_SE", L"Kadouonn.wav");//スタート地点に運ばれてきたときの音
		LoadSound(L"SAVE_SE", L"Save.wav"); // 中間地点通過時のSE
		LoadSound(L"GOAL_SE", L"Goal.wav"); // ゴール通過時のSE
		LoadSound(L"GET_SE", L"Get.wav"); // 鍵取得時のSE
		LoadSound(L"SHUTTER_SE", L"Shutter.wav");//シャッター閉まるときの音
		LoadSound(L"SHUTTER2_SE", L"Shutter2.wav");//シャッター開く時の音
		LoadSound(L"HAMMER_SE", L"hammer.wav");//ハンマーが振り落とされる時の音

	}

	void Scene::OnCreate(){
		try {
			CreateResourses();

			//クリアする色を設定
			SetClearColor(Col4(1.0f));
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
			for (int i = 1; i < 7; i++) {
				ResetScore(i);
			}

			m_bgm = audioPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
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
		else if (event->m_MsgStr == L"ToMovieStage") {
			ResetActiveStage<TitleMovieStage>();
			m_scene = 15;
		}
		if (event->m_MsgStr == L"ToMagTestStage") {
			ResetActiveStage<PlayerMagTestStage>();
			m_scene = 10;
		}
	}

}
//end basecross
