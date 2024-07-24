/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		m_View = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<DuoCamera>();
		m_View->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateObjGroup() {
		CreateSharedObjectGroup(L"BeltConveyorLeft");
		CreateSharedObjectGroup(L"BeltConveyorRight");
		CreateSharedObjectGroup(L"BeltConveyorSideLeft");
		CreateSharedObjectGroup(L"BeltConveyorSideRight");
	}

	void GameStage::PlayBGM(wstring sound) {
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(sound, XAUDIO2_LOOP_INFINITE, 0.8f);
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void GameStage::OnCreate() {
		try {
			m_ptrScene = App::GetApp()->GetScene<Scene>();
			m_ptrScene ->SetGameState(GameState::MainGame);
			m_ptrScene->SetPauseNum(0);
			m_ptrScene->SetResultNum(0);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateObjGroup();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring strMap = DataDir + L"Maps\\";

			auto ptrCamera = dynamic_pointer_cast<DuoCamera>(m_View->GetCamera());

			switch (m_ptrScene->GetStageNum()) {
			case 1:
				CreateBackGround(L"BACKGROUND1");
				m_GameStageCsv.SetFileName(strMap + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_firstStageHeight);
				}

				break;
			case 2:
				CreateBackGround(L"BACKGROUND2");
				m_GameStageCsv.SetFileName(strMap + L"Stage2.csv");
				PlayBGM(L"GAMESTAGE2_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_secondStageHeight);
				}
				break;
			case 3:
				CreateBackGround(L"BACKGROUND3");
				m_GameStageCsv.SetFileName(strMap + L"Stage3.csv");
				PlayBGM(L"GAMESTAGE3_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_thirdStageHeight);
				}
				break;
			case 4:
				CreateBackGround(L"BACKGROUND4");
				m_GameStageCsv.SetFileName(strMap + L"Stage4.csv");
				PlayBGM(L"GAMESTAGE4_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_fourthStageHeight);
				}
				break;
			case 5:
				CreateBackGround(L"BACKGROUND5");
				m_GameStageCsv.SetFileName(strMap + L"Stage5.csv");
				PlayBGM(L"GAMESTAGE5_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_fifthStageHeight);
				}
				break;
			case 6:
				CreateBackGround(L"BACKGROUND6");
				m_GameStageCsv.SetFileName(strMap + L"Stage6.csv");
				PlayBGM(L"GAMESTAGE6_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_sixthStageHeight);
				}
				break;
			default:
				m_GameStageCsv.SetFileName(strMap + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				if (ptrCamera) {
					//�J�����̃X�e�[�W���Ƃ̍����̐ݒ�
					ptrCamera->SetCameraHeight(m_firstStageHeight);
				}
				break;
			}
			m_GameStageCsv.ReadCsv();
			m_ptrScene->ResetScore(m_ptrScene->GetStageNum());

			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//�v���C���[�I�u�W�F�N�g��ǉ�
			m_ptrPlayer1 = AddGameObject<Player>();
			SetSharedGameObject(L"Player", m_ptrPlayer1);
			m_ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", m_ptrPlayer2);

			CreateCsvObjects();

			AddGameObject<StartMoveObject>(Vec3(1.0f), Vec3(1.0f));
			// ���΃I�u�W�F�N�g��ǉ�
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			//AddGameObject<MoveMetalObject>(Vec3(30, 5, 0));


		}
		catch (...) {
			throw;
		}
	}

	/**
	* @brief �w�i�����֐�
	* @param[in] texkey(�w�i�e�N�X�`���̖��O)
	* @return �߂�l�Ȃ�
	* @details for���[�v�ŕ����̔w�i��\��������
	*/
	void GameStage::CreateBackGround(const wstring& texkey) {
		auto stageNum = m_ptrScene->GetStageNum();
		for (int i = 0; i < 9; i++) {
			AddGameObject<BackGroundSprite2>(Vec3(50, 40, 1.0f), Vec3(-50 + (50 * i),0,0), texkey);
		}
	}

	//�X�e�[�W�N���A���Ɏg�p����UI�i�X�e�[�W�Z���N�g�ɖ߂�A���̃X�e�[�W�ցA�^�C�g���ɖ߂�j
	void GameStage::CreateAnimeSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-850.0f, -50.0f,0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);//�X�e�[�W�Z���N�g��
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-300.0f, -50.0f, 0.0f), Vec2(650.0f, 500.0f), L"NEXTSTAGE", false);//���̃X�e�[�W��
		m_SpVec[1] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(220.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);//�^�C�g���ɖ߂�
		m_SpVec[2] = PtrSp;
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
			m_key2->SetDrawActive(false);
			m_key3->SetDrawActive(false);
		}
		m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(-600.0f, 350.0f, 0.0f));
		m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(0.0f, 350.0f, 0.0f));
		m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(195.0f, 195.0f), Vec3(600.0f, 350.0f, 0.0f));
		m_resultScore = m_score;
		isGoal = true;
	}

	//�Ō�̃X�e�[�W�N���A���Ɏg�p����UI�i�X�e�[�W�Z���N�g�ɖ߂�A�^�C�g���ɖ߂�j
	void GameStage::CreateAnimeSpriteLastStage() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-650.0f, -50.0f, 0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);//�X�e�[�W�Z���N�g��
		PtrSp->SetSelect(true);
		m_SpVec2[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(20.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);//�^�C�g���ɖ߂�
		m_SpVec2[2] = PtrSp;
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
			m_key2->SetDrawActive(false);
			m_key3->SetDrawActive(false);
		}
		m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(-600.0f, 350.0f, 0.0f));
		m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(0.0f, 350.0f, 0.0f));
		m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(190.0f, 190.0f), Vec3(600.0f, 350.0f, 0.0f));
		m_resultScore = m_score;
		isGoal = true;
	}
	//�N���A���̎��̃X�e�[�W�ւƂ��̏���
	//�R���g���[���[���X�e�B�b�N�̂̑�����擾���đI�����ɉ������V�[���ڍs���s��
	void GameStage::ClearResult() {
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			m_ptrScene = App::GetApp()->GetScene<Scene>();
			int ResultNum = m_ptrScene->GetResultNum();
			int StageNum = m_ptrScene->GetStageNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected) {
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLX >= 0.8) {
						ResultNum++;
						if (ResultNum > 2)
						{
							ResultNum = 0;
						}
						m_CntrolLock = true;
						m_Lock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						m_CntrolLock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
				}
				else {
					if (CntlVec[0].fThumbLX == 0.0f && !m_pushButton) {
						m_CntrolLock = false;
					}
				}
			}
		}
	}

	void GameStage::ClearResultLastStage() {
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			int ResultNum = m_ptrScene->GetResultNum();
			int StageNum = m_ptrScene->GetStageNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected) {
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLX >= 0.8) {
						ResultNum++;
						if (ResultNum > 2)
						{
							ResultNum = 0;
						}
						if (ResultNum == 1)
						{
							ResultNum = 2;
						}
						m_CntrolLock = true;
						m_Lock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenuLast(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						if (ResultNum == 1)
						{
							ResultNum = 0;
						}
						m_CntrolLock = true;
						m_ptrScene->SetResultNum(ResultNum);
						ChangeSelectMenuLast(ResultNum);
					}
				}
				else {
					if (CntlVec[0].fThumbLX == 0.0f && !m_pushButton) {
						m_CntrolLock = false;
					}
				}
			}
		}
	}

	void GameStage::ChangeSelectMenu(int num) {
		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if (i == num) {
					shptr->SetSelect(true);
				}
				else { 
					shptr->SetSelect(false);
				}
			}
		}
	}

	void GameStage::ChangeSelectMenuLast(int num) {
		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec2[i].lock();
			if (shptr) {
				if (i == num) {
					shptr->SetSelect(true);
				}
				else {
					shptr->SetSelect(false);
				}
			}
		}
	}

	void GameStage::CreateCsvObjects() {
		auto SavePointGroup = CreateSharedObjectGroup(L"SavePoint"); // �Z�[�u�|�C���g�O���[�v
		auto GroundObjGroup = CreateSharedObjectGroup(L"Ground"); // ���I�u�W�F�N�g�O���[�v
		auto MagAreaGroup = CreateSharedObjectGroup(L"MagnetAreas"); // �}�O�l�b�g�G���A�O���[�v
		auto NMagObjGroup = CreateSharedObjectGroup(L"NMagnets"); // N�}�O�l�b�g�O���[�v
		auto SMagObjGroup = CreateSharedObjectGroup(L"SMagnets"); // S�}�O�l�b�g�O���[�v
		auto MetalObjGroup = CreateSharedObjectGroup(L"MetalObj"); // �����I�u�W�F�N�g(�s��)�O���[�v

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;
		std::shared_ptr<GameObject> ptrMetal;
		std::shared_ptr<GameObject> ptrMoveMetal;
		std::shared_ptr<GameObject> ptrStart;
		std::shared_ptr<GameObject> ptrSavePoint;
		std::shared_ptr<GameObject> ptrGoal;
		std::shared_ptr<GameObject> ptrMoveFloor;
		std::shared_ptr<GameObject> ptrMoveFloorButton;

		auto& LineVec = m_GameStageCsv.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				float posX = (float)((int)j -5) / size;
				float posY = (float)((int)i) / size;
				int TokensNum = stoi(Tokens[j]);


				switch (TokensNum) {
				case 0: //�ʏ�n��
					ptrGround = AddGameObject<Block>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0), L"GROUND_TX");
					GroundObjGroup->IntoGroup(ptrGround);
					break;

				case 1: //����N��
					ptrMag = AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					NMagObjGroup->IntoGroup(ptrMag);
					break;

				case 2: //����S��
					ptrMag = AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					SMagObjGroup->IntoGroup(ptrMag);
					break;

				case 3: //�����I�u�W�F�N�g
					ptrMetal = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					MetalObjGroup->IntoGroup(ptrMetal);
					break;

				case 4: //���E�ɓ��������̃I�u�W�F�N�g
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), RIGHT_VEC, 3.5f);
					break;

				case 5: //�㉺�ɓ��������̃I�u�W�F�N�g
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), UP_VEC, 3.5f);
					break;

				case 6://�󂹂��
					AddGameObject<BreakWall>(Vec3(posX, -posY + m_CSVHeight, 0), Vec3(0.0f));
					break;

				case 7://�{�^���������瓮����
					ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(8.2f, 0.9f, 0.9f), Vec3(posX + 5.0f, -posY + m_CSVHeight, 0), LEFT_VEC);
					SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
					break;

				case 8://�����������p�{�^��
					ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(posX, -posY + m_CSVHeight - 0.47, 0));
					SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
					break;

				case 9://�x���g�R���x�A�E���[
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 10://�x���g�R���x�A�E���^��
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<RightGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 11://�x���g�R���x�A�����[
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 12://�x���g�R���x�A�����^��
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					AddGameObject<LeftGuide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, -0.5));
					break;

				case 13: //�X�^�[�g
					ptrStart = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					SetSharedGameObject(L"Start", ptrStart);
					break;

				case 14: //�Z�[�u�|�C���g
					ptrSavePoint = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1, 0));
					SavePointGroup->IntoGroup(ptrSavePoint);
					break;

				case 15: //�S�[��
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1, 0));
					SetSharedGameObject(L"Goal", ptrGround);
					break;

				case 16: //���ԉE���
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_RIGHT, 60.0f, STATE_METAL, STATE_NONE);
					break;

				case 17: //���ԍ����
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_LEFT, 80.0f, STATE_NONE, STATE_METAL);
					break;

				case 18: //��
					AddGameObject<CoinObject>(Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 19: //���͂̂Ȃ��n���}�[
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0),STATE_NONE);
					break;

				case 20: //2*2�̒n�ʃI�u�W�F�N�g
					ptrGround = AddGameObject<Block>(Vec3(2.0f,2.0f,1.0f) / size, Vec3(posX+0.5, -posY + m_CSVHeight-0.5, 0),L"CONCRETE2_TX");
					break;

				case 21: //3*3�̒n�ʉ��W�F�N�g
					ptrGround = AddGameObject<Block>(Vec3(3.0f,3.0f,1.0f) / size, Vec3(posX+1, -posY + m_CSVHeight-1, 0),L"CONCRETE3_TX");
					break;

				case 22: //1P����ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight,0.5), 1);
					break;

				case 23: //1P�����ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 2);
					break;

				case 24: //1P���^�������ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 3);
					break;

				case 25: //2P����ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 4);
					break;

				case 26: //2P�����ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 5);
					break;

				case 27: //2P���^�������ɍs���K�C�h
					AddGameObject<Guide>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0.5), 6);
					break;

				case 28://S�ɂ̃n���}�[
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0), STATE_MAG_S);
					break;

				case 29://N�ɂ̃n���}�[
					AddGameObject<HammerObject>(Vec3(posX, -posY + m_CSVHeight, 0), STATE_MAG_N);
					break;

				default:
					break;
				}
			}
		}
	}

	void GameStage::CreateKeyLoad(const int scene, const Vec3 pos) {
		int score = App::GetApp()->GetScene<Scene>()->GetScore(scene);
		if (m_key1 != NULL) {
			m_key1->SetDrawActive(false);
		}
		if (m_key2 != NULL) {
			m_key2->SetDrawActive(false);
		}
		if (m_key3 != NULL) {
			m_key3->SetDrawActive(false);
		}
		switch (score) {
		case 0:
			m_key1 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 1:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 2:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		default:
			m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			m_key3 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		}
	}


	void GameStage::OnUpdate()
	{
		m_InputHandler.PushHandler(GetThis<GameStage>());
		int stageNum = m_ptrScene->GetStageNum();
		if (m_ptrScene->GetGameState() == GameState::GameClear)
		{
			if (stageNum != 6)
			{
				if (m_Clear <= false)
				{
					m_Clear = true;
					CreateAnimeSprite();
				}
				ClearResult();
			}
			else
			{
				if (m_Clear <= false)
				{
					m_Clear = true;
					CreateAnimeSpriteLastStage();
				}
				ClearResultLastStage();
			}
			
		}
		m_score = m_ptrScene->GetScore(m_ptrScene->GetStageNum());
		if (m_score > m_previousScore) {
			m_previousScore = m_score;
			CreateKeyLoad(m_ptrScene->GetStageNum(), Vec3(-740.0f, 400.0f, 0.0f));
		}
		if (m_ptrScene->GetGameState() == GameState::Pause)
		{
			Menu();
		}
		CollisionSwitch();

		if (isGoal) {
			m_time--;

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			auto pos = m_ptrPlayer1->GetComponent<Transform>()->GetPosition();
			
			if (m_resultScore >= 1) {
				if (!isScore1) {
					if (m_time <= 90.0f) {
						m_key1->SetDrawActive(false);
						m_key1 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(-600.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x , pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore1 = true;
					}
				}
			}
			if (m_resultScore >= 2) {
				if (m_time <= 50.0f) {
					if (!isScore2) {
						m_key2->SetDrawActive(false);
						m_key2 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(0.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x , pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore2 = true;
					}
				}
			}
			if (m_resultScore >= 3) {
				if (m_time <= 10.0f) {
					if (!isScore3) {
						m_key3->SetDrawActive(false);
						m_key3 = AddGameObject<SelectSprite>(L"KEY", true, Vec2(200.0f, 200.0f), Vec3(600.0f, 350.0f, 0.0f));
						XAPtr->Start(L"GET_SE", 0, 10.0f);
						AddGameObject<EffectPlayer>(Vec3(pos.x + 5.0f, pos.y -2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						AddGameObject<EffectPlayer>(Vec3(pos.x - 5.0f, pos.y - 2.0f, 0.0f), Vec3(0.5f), L"GameClear");
						isScore3 = true;
					}
				}
			}
		}

		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];
		//Start�EBack�{�^�����������Ń^�C�g���ɖ߂�
		if (firstPad.wButtons & BUTTON_START && firstPad.wButtons & BUTTON_BACK ||
			secondPad.wButtons & BUTTON_START && secondPad.wButtons & BUTTON_BACK) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}
	void GameStage::OnPushSTART()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		if (m_ptrScene->GetGameState() == GameState::MainGame)
		{
			ptrPlayer->SetUpdateActive(false);
			ptrPlayer2->SetUpdateActive(false);
			m_ptrScene->SetGameState(GameState::Pause);

			CreatePauseSprite();
		}
		else if (m_ptrScene->GetGameState() == GameState::Pause)
	{
			ptrPlayer->SetUpdateActive(true);
			ptrPlayer2->SetUpdateActive(true);
			m_ptrScene->SetGameState(GameState::MainGame);
		}
	}
	//�I�v�V�����{�^���������ƃ|�[�Y���đ��삷��@�\
	void GameStage::Menu() {
		if (m_ptrScene->GetGameState() == GameState::Pause)
		{
			auto m_ptrScene = App::GetApp()->GetScene<Scene>();
			int	 PauseNum = m_ptrScene->GetPauseNum();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			if (CntlVec[0].bConnected) {
				m_ptrScene->ResetScore(m_ptrScene->GetStageNum());
				if (!m_CntrolLock) {
					if (CntlVec[0].fThumbLY >= 0.8) {
						PauseNum--;
						if (PauseNum < 0)
						{
							PauseNum = 2;
						}
						m_CntrolLock = true;
						m_ptrScene->SetPauseNum(PauseNum);
						ChangeSelectPauseMenu(PauseNum);
					}
					else if (CntlVec[0].fThumbLY <= -0.8f) {
						PauseNum++;
						if (PauseNum > 2) {
							PauseNum = 0;
						}
						m_CntrolLock = true;
						m_ptrScene->SetPauseNum(PauseNum);
						ChangeSelectPauseMenu(PauseNum);
					}
				}
				else {
					if (CntlVec[0].fThumbLY == 0.0f && !m_pushButton) {
						m_CntrolLock = false;
					}
				}
			}
		}
	}

	//�|�[�Y���j���[�Ŏg�p����X�v���C�g����
	void GameStage::CreatePauseSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,500.0f,0.0f), Vec2(800.0f, 750.0f), L"BACKTOSTAGESELECT", false);
		m_SpVec[0] = PtrSp;
		PtrSp->SetSelect(true);
		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,300.0f,0.0f), Vec2(800.0f, 750.0f), L"RETRY", false);
		m_SpVec[1] = PtrSp;
		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-400.0f,70.0f,0.0f), Vec2(800.0f, 750.0f), L"BACKTOTITLE", false);
		m_SpVec[2] = PtrSp;
		AddGameObject<PauseSprite>(L"PAUSE_BACK", true, Vec2(700.0f, 750.0f), Vec3(0.0f),Col4(1.0f),true);
		AddGameObject<PauseSprite>(L"MENU", true, Vec2(700.0f, 500.0f), Vec3(0.0f, 300.0f, 0.0f), Col4(1.0f), true);
	}

	void GameStage::ChangeSelectPauseMenu(int num) {

		for (int i = 0; i < 3; i++) {
			shared_ptr<FlashSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if ((i) == num) {
					shptr->SetSelect(true);
				}
				else {
					shptr->SetSelect(false);
				}
			}
		}
	}

	void GameStage::OnPushB()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		if (!m_pushButton)
		{
			if (ptrPlayer->IsGoal() && ptrPlayer2->IsGoal()) {
				if (m_ptrScene->GetGameState() == GameState::GameClear)
				{
					m_pushButton = true;
					AddGameObject<FadeOut>(L"FADE_WHITE");
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);

					int ResultNum = m_ptrScene->GetResultNum();
					m_Lock = true;
					m_CntrolLock = true;
					int StageNum = m_ptrScene->GetStageNum();

					if (ResultNum == 0)
					{
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
					}
					if (ResultNum == 1)
					{
						StageNum++;

						int m_score = 0;
						for (int i = 1; i < 7; i++) {
							m_score += m_ptrScene->GetScore(i);
						}
						if (StageNum <= 3) {
							m_ptrScene->SetStageNum(StageNum);
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						if (StageNum == 4) {
							if (m_score >= 7) {
								m_ptrScene->SetStageNum(StageNum);
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
							}
							else {
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
							}
						}
						if (StageNum == 5) {
							if (m_score >= 10) {
								m_ptrScene->SetStageNum(StageNum);
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
							}
							else {
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
							}
						}
						if (StageNum == 6) {
							if (m_score >= 13) {
								m_ptrScene->SetStageNum(StageNum);
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
							}
							else {
								PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
							}
						}
						if (StageNum > 6) {
							PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
						}
					}

					if (ResultNum == 2)
					{

						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
					}
				}
			}
			if (m_ptrScene->GetGameState() == GameState::Pause)
			{
				m_pushButton = true;
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				AddGameObject<FadeOut>(L"FADE_WHITE");
				int	 PauseNum = m_ptrScene->GetPauseNum();
				m_pushButton = true;
				m_CntrolLock = true;

				//m_ptrScene->SetGameState(GameState::IsSelect);

				if (PauseNum == 0)
				{
					PtrScene->ResetScore(PtrScene->GetStageNum());
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
				}
				if (PauseNum == 1)
				{
					PtrScene->ResetScore(PtrScene->GetStageNum());
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

				}
				if (PauseNum == 2)
				{
					PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
				}
			}
		}
	}

	void GameStage::CollisionSwitch() {
		GroupCollisionSwitch(L"Ground");
	}

	void GameStage::GroupCollisionSwitch(wstring groupStr) {
		Vec3 player1Pos = m_ptrPlayer1->GetComponent<Transform>()->GetWorldPosition();
		Vec3 player2Pos = m_ptrPlayer2->GetComponent<Transform>()->GetWorldPosition();

		auto ptrGroup = GetSharedObjectGroup(groupStr);
		auto& GroupVec = ptrGroup->GetGroupVector();
		for (auto& v : GroupVec) {
			auto shObj = v.lock();
			if (shObj) {
				auto shGround = dynamic_pointer_cast<GameObject>(shObj);
				if (shGround) {
					auto shGroundPos = shGround->GetComponent<Transform>()->GetWorldPosition();
					auto shaGroundColl = shGround->GetComponent<CollisionObb>();
					if (length(player1Pos - shGroundPos) <= 1.5f) {
						//shaGroundColl->SetDrawActive(true);
						shaGroundColl->SetUpdateActive(true);
					}
					else if (shaGroundColl->IsUpdateActive()) {
						//shaGroundColl->SetDrawActive(false);
						shaGroundColl->SetUpdateActive(false);
					}

					if (length(player2Pos - shGroundPos) <= 1.5f) {
						//shaGroundColl->SetDrawActive(true);
						shaGroundColl->SetUpdateActive(true);
					}
				}
			}
		}
	}

}
//end basecross
