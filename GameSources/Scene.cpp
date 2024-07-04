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

	// �T�E���h�̓ǂݍ���
	void Scene::LoadSound(const wstring& soundName, const wstring& soundDataName){
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}



	void Scene::CreateResourses() {

		//�e�N�X�`��
		LoadTexture(L"Player01_TX", L"pcube01.png"); // Player�p�e�N�X�`��
		LoadTexture(L"Player02_TX", L"pcube02.png");
		LoadTexture(L"Player03_TX", L"pcube03.png");
		LoadTexture(L"TYPEALL_TX", L"MagnetAreaW.png"); // ���̓G���A�p�e�N�X�`��
		LoadTexture(L"TYPEALL_N_TX", L"MagnetAreaB.png"); // ���̓G���A�p�e�N�X�`��
		LoadTexture(L"TYPEALL_B_TX", L"MagnetAreaE.png"); // ���̓G���A�p�e�N�X�`��
		LoadTexture(L"BPUSH", L"PushB.png"); // B�{�^���p
		LoadTexture(L"RBPUSH", L"PushRB.png"); // RB�{�^���p
		LoadTexture(L"READY", L"StandBy.png"); // STANDBY(����)
		LoadTexture(L"CLEAR", L"StageClear.png"); // �X�e�[�W�N���A
		LoadTexture(L"BACKTOTITLE", L"BackToTitle.png");//�^�C�g���ɖ߂镶��UI
		LoadTexture(L"CHECKPOINT_TX", L"CheckPoint.png"); // ���Ԓn�_

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

		LoadTexture(L"EASY", L"Easy.png");//��Փx�\���̃X�v���C�g
		LoadTexture(L"NORMAL", L"Normal.png");
		LoadTexture(L"HARD", L"Hard.png");


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

		LoadTexture(L"FADE_WHITE", L"Fade_White.png"); // �t�F�[�h�p
		LoadTexture(L"FADE_BLACK", L"Fade_Black.png"); // �t�F�[�h�p
		LoadTexture(L"SFADE", L"SFade.png");//�V�[���؂�ւ��ł����V���b�^�[�݂����ɕ���p�̃X�v���C�g�iS�ɁAN�Ɂj
		LoadTexture(L"NFADE", L"NFade.png");

		LoadTexture(L"MGNETN_TX", L"Tile_MGN.png"); // N�Ƀu���b�N
		LoadTexture(L"MGNETS_TX", L"Tile_MGS.png"); // S�Ƀu���b�N
		LoadTexture(L"GROUND_TX", L"Ground.png"); // ���I�u�W�F�N�g
		LoadTexture(L"CONCRETE2_TX", L"Ground2.png"); // ���I�u�W�F�N�g(2x2)
		LoadTexture(L"CONCRETE3_TX", L"Ground3.png"); // ���I�u�W�F�N�g(3x3)
		LoadTexture(L"METAL_TX", L"Tile_Metal.png"); // �����I�u�W�F�N�g
		LoadTexture(L"MOVEFLOOR_TX", L"MoveFloor.png"); // �ړ����p

		LoadTexture(L"TENNSENNRED_TX", L"tennsennRed.png"); // �S�[���ʉ߃`�F�b�N�p(Player1�p�_��)
		LoadTexture(L"RED_TX", L"Red.png"); // �S�[���ʉ߃`�F�b�N�p(Player1�p)
		LoadTexture(L"TENNSENNBLUE_TX", L"tennsennBlue.png"); // �S�[���ʉ߃`�F�b�N�p(Player2�p�_��)
		LoadTexture(L"BLUE_TX", L"Blue.png"); // �S�[���ʉ߃`�F�b�N�p(Player2�p)
		LoadTexture(L"PURPLE_TX", L"Purple.png"); // ���Ԓn�_�̗ւ����p
		LoadTexture(L"GREEN_TX", L"Green.png"); // ���Ԓn�_�̗ւ����p
		LoadTexture(L"TENNSENNTRIANGLERED_TX", L"tennsennTriangleR.png"); // ���Ԓn�_�ʉ߃`�F�b�N�p(Player1�p�_��)
		LoadTexture(L"TRIANGLERED_TX", L"TriangleR.png"); // ���Ԓn�_�ʉ߃`�F�b�N�p(Player1�p)
		LoadTexture(L"TENNSENNTRIANGLEBLUE_TX", L"tennsennTriangleB.png"); // ���Ԓn�_�ʉ߃`�F�b�N�p(Player2�p�_��)
		LoadTexture(L"TRIANGLEBLUE_TX", L"TriangleB.png"); // ���Ԓn�_�ʉ߃`�F�b�N�p(Player2�p)

		LoadTexture(L"1P", L"1P.png"); // �o�i�[(Player1�p)
		LoadTexture(L"2P", L"2P.png"); // �o�i�[(Player2�p)
		LoadTexture(L"KEY", L"key.png"); // ��
		LoadTexture(L"NOKEY", L"NoKey.png"); // ��(��)
		LoadTexture(L"ROCK", L"rock.png"); // �{��
		LoadTexture(L"KEY7", L"key7.png"); // ��7�K�v
		LoadTexture(L"KEY10", L"key10.png"); // ��10�K�v
		LoadTexture(L"KEY13", L"key13.png"); // ��13�K�v

		LoadTexture(L"DEATHEFFECT", L"DeathEffect.png");

		//�K�C�h�̉摜
		LoadTexture(L"GUIDEREDUP_TX", L"GuideRedUp.png"); // �����(Player1�p)
		LoadTexture(L"GUIDEREDDOWM_TX", L"GuideRedDown.png"); // ������(Player1�p)
		LoadTexture(L"GUIDEREDCENTER_TX", L"GuideRedCenter.png"); // ������(Player1�p)
		LoadTexture(L"GUIDEBLUEUP_TX", L"GuideBlueUp.png"); // �����(Player2�p)
		LoadTexture(L"GUIDEBLUEDOWM_TX", L"GuideBlueDown.png"); // ������(Player2�p)
		LoadTexture(L"GUIDEBLUECENTER_TX", L"GuideBlueCenter.png"); // ������(Player2�p)

		// ���I�u�W�F�N�g
		LoadBoneModel(L"Key", L"Key_MESH",L"Key_MESH_TAN");

		//Player1
		LoadBoneModel(L"Brack", L"PlayerBrack_MESH", L"PlayerBrack_MESH_TAN"); //����
		LoadBoneModel(L"Red", L"PlayerRed_MESH", L"PlayerRed_MESH_TAN"); //N��
		LoadBoneModel(L"Redanger", L"PlayerRedanger_MESH", L"PlayerRedanger_MESH_TAN"); //N��(�{���)
		LoadBoneModel(L"blacksmile", L"PlayerBrackSmile_MESH", L"PlayerBrackSmile_MESH_TAN"); //����(�ɂ�����)
		LoadBoneModel(L"Redsmile", L"PlayerRedSmile_MESH", L"PlayerRedSmile_MESH_TAN"); //N��(�ɂ�����)

		//Player2
		LoadBoneModel(L"Brack", L"Player2Brack_MESH", L"Player2Brack_MESH_TAN"); //����
		LoadBoneModel(L"Brue", L"Player2Blue_MESH", L"Player2Blue_MESH_TAN"); //S��
		LoadBoneModel(L"Blueanger", L"Player2Blueanger_MESH", L"Player2Blueanger_MESH_TAN");// S��(�{���)
		LoadBoneModel(L"blacksmile", L"Player2BrackSmile_MESH", L"Player2BrackSmile_MESH_TAN");// ����(�ɂ�����)
		LoadBoneModel(L"Greensmile", L"Player2BlueSmile_MESH", L"Player2BlueSmile_MESH_TAN"); // S��(�ɂ�����)

		//�x���g�R���x�A
		LoadTexture(L"GUIDER_TX", L"GuideRight.png"); // �x���g�R���x�A�̉E�������
		LoadTexture(L"GUIDEL_TX", L"GuideLeft.png"); // �x���g�R���x�A�̍��������
		RegisterMultiMesh(L"CONVEYOR", L"m_Convayor", true); // �x���g�R���x�A
		RegisterMultiMesh(L"SIDE_CONVEYOR", L"s_Convayor", true); // �x���g�R���x�A(�[)

		// �ւ���
		LoadStaticModelMesh(L"metalring04", L"RingObject_MESH");
		// ����
		LoadStaticModelMesh(L"GearObj", L"GearObject_MESH");
		// �����
		LoadBoneModel(L"BreakWall", L"BreakWall_MESH", L"BreakWall_MESH_TAN");
		LoadTexture(L"BREAK_TX", L"BreakWallTex.png");
		// �n���}�[(��&��&��)
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
		LoadSound(L"GAMESTAGE1_BGM", L"GameStage1.wav");//�X�e�[�W1~6
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
		LoadSound(L"OPERATION_SE", L"Kadouonn.wav");//�X�^�[�g�n�_�ɉ^�΂�Ă����Ƃ��̉�
		LoadSound(L"SAVE_SE", L"Save.wav"); // ���Ԓn�_�ʉߎ���SE
		LoadSound(L"GOAL_SE", L"Goal.wav"); // �S�[���ʉߎ���SE
		LoadSound(L"GET_SE", L"Get.wav"); // ���擾����SE
		LoadSound(L"SHUTTER_SE", L"Shutter.wav");//�V���b�^�[�܂�Ƃ��̉�
		LoadSound(L"SHUTTER2_SE", L"Shutter2.wav");//�V���b�^�[�J�����̉�
		LoadSound(L"HAMMER_SE", L"hammer.wav");//�n���}�[���U�藎�Ƃ���鎞�̉�

	}

	void Scene::OnCreate(){
		try {
			CreateResourses();

			//�N���A����F��ݒ�
			SetClearColor(Col4(1.0f));
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
