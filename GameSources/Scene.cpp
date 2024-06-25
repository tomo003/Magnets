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
	void Scene::LoadTexture(const wstring& UseTextureName, const wstring& TextureDataName) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Texture\\" + TextureDataName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	// �ÓI���f���̓ǂݍ���
	void Scene::LoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,MeshResource::CreateStaticModelMesh(dataDir+ L"Model//",  staticModelbmfName + L".bmf")
		);
	}

	// �{�[�����f���̓ǂݍ���
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
	void Scene::LoadSound(const wstring& soundName, const wstring& soundDataName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}



	void Scene::CreateResourses() {

		//�e�N�X�`��
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
		LoadTexture(L"BACKTOTITLE", L"BackToTitle.png");//�^�C�g���ɖ߂镶��UI
		LoadTexture(L"CHECKPOINT_TX", L"CheckPoint.png");

		LoadTexture(L"PAUSE_BACK", L"Pause.png");//�|�[�Y���j���[�̃E�B���h�E�w�i
		LoadTexture(L"MENU", L"Menu.png");//�|�[�Y���j���[�ŕ\������郁�j���[����UI
		LoadTexture(L"RETRY", L"Retry.png");//�|�[�Y���j���[�ŕ\������郊�g���C����UI

		LoadTexture(L"BACKGROUND1", L"BackA.png");//�X�e�[�W1�̔w�i
		LoadTexture(L"BACKGROUND2", L"BackB.png");//�X�e�[�W2�̔w�i
		LoadTexture(L"BACKGROUND3", L"BackC.png");//�X�e�[�W3�̔w�i
		LoadTexture(L"BACKGROUND4", L"BackD.png");//�X�e�[�W4�̔w�i
		LoadTexture(L"BACKGROUND5", L"BackE.png");//�X�e�[�W5�̔w�i
		LoadTexture(L"BACKGROUND6", L"BackF.png");//�X�e�[�W6�̔w�i

		LoadTexture(L"TITLE", L"title.png");//�^�C�g�����S

		LoadTexture(L"STAGE1", L"Stage1.png");//�X�e�[�W�Z���N�g�V�[���Ɏg���u�X�e�[�W1�`6�v�̃X�N�V���X�v���C�g
		LoadTexture(L"STAGE2", L"Stage2.png");
		LoadTexture(L"STAGE3", L"Stage3.png");
		LoadTexture(L"STAGE4", L"Stage4.png");
		LoadTexture(L"STAGE5", L"Stage5.png");
		LoadTexture(L"STAGE6", L"Stage6.png");

		LoadTexture(L"STAGE1UI", L"Stage1UI.png");//�X�e�[�W�Z���N�g�V�[���Ɏg���u�X�e�[�W1�`6�v�܂ł̕���UI
		LoadTexture(L"STAGE2UI", L"Stage2UI.png");
		LoadTexture(L"STAGE3UI", L"Stage3UI.png");
		LoadTexture(L"STAGE4UI", L"Stage4UI.png");
		LoadTexture(L"STAGE5UI", L"Stage5UI.png");
		LoadTexture(L"STAGE6UI", L"Stage6UI.png");
		LoadTexture(L"STAGESELECT", L"StageSelect.png");//�X�e�[�W�Z���N�g�V�[���Ɏg������̃X�e�[�W�Z���N�g����
		LoadTexture(L"CURSOR", L"Cursor.png");//�X�e�[�W�Z���N�g�V�[���Ɏg�����F�J�[�\���X�v���C�g

		LoadTexture(L"BACKTOSTAGESELECT", L"BackToStageSelect.png");//�X�e�[�W�Z���N�g�V�[���ɖ߂镶��UI
		LoadTexture(L"NEXTSTAGE", L"NextStage.png");//���̃X�e�[�W�֕���UI

		LoadTexture(L"FADE_WHITE", L"Fade_White.png");
		LoadTexture(L"FADE_BLACK", L"Fade_Black.png");
		LoadTexture(L"SFADE", L"SFade.png");//�V�[���؂�ւ��ł����V���b�^�[�݂����ɕ���p�̃X�v���C�g�iS�ɁAN�Ɂj
		LoadTexture(L"NFADE", L"NFade.png");

		LoadTexture(L"MGNETN_TX", L"Tile_MGN.png");
		LoadTexture(L"MGNETS_TX", L"Tile_MGS.png");
		LoadTexture(L"BROCK_TX", L"Tile_Normal.png");
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

		LoadTexture(L"DEATHEFFECT", L"DeathEffect.png");

		//�K�C�h�̉摜
		LoadTexture(L"GUIDEREDUP_TX", L"GuideRedUp.png");
		LoadTexture(L"GUIDEREDDOWM_TX", L"GuideRedDown.png");
		LoadTexture(L"GUIDEREDCENTER_TX", L"GuideRedCenter.png");
		LoadTexture(L"GUIDEBLUEUP_TX", L"GuideBlueUp.png");
		LoadTexture(L"GUIDEBLUEDOWM_TX", L"GuideBlueDown.png");
		LoadTexture(L"GUIDEBLUECENTER_TX", L"GuideBlueCenter.png");

		LoadStaticModelMesh(L"01", L"Player01_MESH");
		LoadStaticModelMesh(L"02", L"Player02_MESH");
		LoadStaticModelMesh(L"03", L"Player03_MESH");

		LoadBoneModel(L"Key", L"Key_MESH",L"Key_MESH_TAN");

		//Player1
		LoadBoneModel(L"Brack", L"PlayerBrack_MESH", L"PlayerBrack_MESH_TAN");//����
		LoadBoneModel(L"Brue", L"PlayerBlue_MESH", L"PlayerBlue_MESH_TAN");//S��
		LoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN");//N��
		LoadBoneModel(L"Redanger", L"PlayerRedanger_MESH", L"PlayerRedanger_MESH_TAN");//N��
		LoadBoneModel(L"blacksmile", L"PlayerBrackSmile_MESH", L"PlayerBrackSmile_MESH_TAN");//����
		LoadBoneModel(L"Redsmile", L"PlayerRedSmile_MESH", L"PlayerRedSmile_MESH_TAN");//N��

		//Player2
		LoadBoneModel(L"Brack", L"Player2Brack_MESH", L"Player2Brack_MESH_TAN");
		LoadBoneModel(L"Brue", L"Player2Blue_MESH", L"Player2Blue_MESH_TAN");
		LoadBoneModel(L"Blueanger", L"Player2Blueanger_MESH", L"Player2Blueanger_MESH_TAN");
		LoadBoneModel(L"Red", L"Player2Red_MESH", L"Player2Red_MESH_TAN");
		LoadBoneModel(L"blacksmile", L"Player2BrackSmile_MESH", L"Player2BrackSmile_MESH_TAN");
		LoadBoneModel(L"Greensmile", L"Player2BlueSmile_MESH", L"Player2BlueSmile_MESH_TAN");

		//�x���g�R���x�A
		wstring dataDir = App::GetApp()->GetDataDirWString();
		auto multiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(dataDir, L"m_Convayor.bmf");
		App::GetApp()->RegisterResource(L"CONVEYOR", multiModelMesh);
		auto multiModelMesh2 = MultiMeshResource::CreateBoneModelMultiMesh(dataDir, L"s_Convayor.bmf");
		App::GetApp()->RegisterResource(L"SIDE_CONVEYOR", multiModelMesh2);

		// �ւ���
		LoadStaticModelMesh(L"metalring04", L"RingObject_MESH");
		// ����
		LoadStaticModelMesh(L"GearObj", L"GearObject_MESH");
		// �����
		LoadBoneModel(L"BreakWall", L"BreakWall_MESH", L"BreakWall_MESH_TAN");
		LoadTexture(L"BREAK_TX", L"BreakWallTex.png");
		// �n���}�[(�ԁ���)
		LoadBoneModel(L"Hammer Red", L"Hammer_Red_MESH", L"Hammer_Red_MESHTAN");
		LoadBoneModel(L"Hammer Green", L"Hammer_Blue_MESH", L"Hammer_Blue_MESHTAN");
		LoadBoneModel(L"Hammer Black", L"Hammer_Black_MESH", L"Hammer_Black_MESHTAN");
		// �n���}�[�G���A(�m���r����)
		LoadTexture(L"REDAREA_TX", L"HummerArea_Red.png");
		LoadTexture(L"BULEAREA_TX", L"HummerArea_Bule.png");
		LoadTexture(L"WHITEAREA_TX", L"HummerArea_White.png");

		//BGM
		LoadSound(L"TITLE_BGM",L"Title.wav");//�^�C�g���V�[��
		LoadSound(L"STANDBY_BGM",L"StandBy.wav");//���������V�[��
		LoadSound(L"GAMESTAGE1_BGM",L"GameStage1.wav");//�X�e�[�W1~6
		LoadSound(L"GAMESTAGE2_BGM", L"GameStage2.wav");
		LoadSound(L"GAMESTAGE3_BGM", L"GameStage3.wav");
		LoadSound(L"GAMESTAGE4_BGM", L"GameStage4.wav");
		LoadSound(L"GAMESTAGE5_BGM", L"GameStage5.wav");
		LoadSound(L"GAMESTAGE6_BGM", L"GameStage6.wav");

		//���ʉ�
		LoadSound(L"JUMP_SE", L"Jump.wav");//�W�����v
		LoadSound(L"UNION_SE", L"Union.wav");//���΂ł��������Ƃ�
		LoadSound(L"BUTTON_SE", L"Decition.wav");//�{�^���������Ƃ��̌��艹
		LoadSound(L"STOP_SE", L"Gachan.wav");//�X�^�[�g�n�_�ɉ^�΂�Ă��Ē�~�����Ƃ��̉�
		LoadSound(L"KADOU_SE", L"Kadouonn.wav");//�X�^�[�g�n�_�ɉ^�΂�Ă����Ƃ��̉�
		LoadSound(L"SAVE_SE", L"Save.wav");
		LoadSound(L"GOAL_SE", L"Goal.wav");
		LoadSound(L"GET_SE", L"Get.wav");
		LoadSound(L"SHUTTER_SE", L"Shutter.wav");//�V���b�^�[�܂�Ƃ��̉�
		LoadSound(L"SHUTTER2_SE", L"Shutter2.wav");//�V���b�^�[�J�����̉�


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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToMagTestStage");
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
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
		if (event->m_MsgStr == L"ToMagTestStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<PlayerMagTestStage>();
			m_scene = 10;
		}
	}

}
//end basecross
