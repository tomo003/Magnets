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
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<DuoCamera>();
		PtrView->SetCamera(PtrCamera);
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
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(sound, XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void GameStage::OnCreate() {
		try {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene ->SetGameState(GameState::MainGame);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateObjGroup();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			switch (PtrScene->GetStageNum()) {
			case 1:
				CreateBackGround(L"BACKGROUND1");
				m_GameStageCsv.SetFileName(DataDir + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				break;
			case 2:
				CreateBackGround(L"BACKGROUND2");
				m_GameStageCsv.SetFileName(DataDir + L"Stage2.csv");
				PlayBGM(L"GAMESTAGE2_BGM");
				break;
			case 3:
				CreateBackGround(L"BACKGROUND3");
				m_GameStageCsv.SetFileName(DataDir + L"Stage3.csv");
				PlayBGM(L"GAMESTAGE3_BGM");
				break;
			case 4:
				CreateBackGround(L"BACKGROUND4");
				m_GameStageCsv.SetFileName(DataDir + L"Stage4.csv");
				PlayBGM(L"GAMESTAGE4_BGM");
				break;
			case 5:
				CreateBackGround(L"BACKGROUND5");
				m_GameStageCsv.SetFileName(DataDir + L"Stage5.csv");
				PlayBGM(L"GAMESTAGE5_BGM");
				break;
			case 6:
				CreateBackGround(L"BACKGROUND6");
				m_GameStageCsv.SetFileName(DataDir + L"Stage6.csv");
				PlayBGM(L"GAMESTAGE6_BGM");
				break;
			default:
				m_GameStageCsv.SetFileName(DataDir + L"Stage1.csv");
				PlayBGM(L"GAMESTAGE1_BGM");
				break;
			}
			m_GameStageCsv.ReadCsv();


			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//�v���C���[�I�u�W�F�N�g��ǉ�
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

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
		for (int i = 0; i <= 5; i++) {
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(-50 + (40 * i),0,0), texkey);
		}
	}

	void GameStage::CreateAnimeSprite() {
		auto PtrSp = AddGameObject<FlashSprite>(
			Vec3(-850.0f, -50.0f,0.0f), Vec2(670.0f, 500.0f), L"BACKTOSTAGESELECT", false);
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(-300.0f, -50.0f, 0.0f), Vec2(650.0f, 500.0f), L"NEXTSTAGE", false);
		m_SpVec[1] = PtrSp;

		PtrSp = AddGameObject<FlashSprite>(
			Vec3(220.0f, -65.0f, 0.0f), Vec2(690.0f, 500.0f), L"BACKTOTITLE", false);
		m_SpVec[2] = PtrSp;
	}

	void GameStage::ClearResult() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::GameClear)
		{
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int ResultNum = PtrScene->GetResultNum();
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
						PtrScene->SetResultNum(ResultNum);
						ChangeSelectMenu(ResultNum);
					}
					else if (CntlVec[0].fThumbLX <= -0.8) {
						ResultNum--;
						if (ResultNum < 0) {
							ResultNum = 2;
						}
						m_CntrolLock = true;
						PtrScene->SetResultNum(ResultNum);
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

	void GameStage::CreateCsvObjects() {
		auto SavePointGroup = CreateSharedObjectGroup(L"SavePoint");

		std::shared_ptr<GameObject> ptrMoveMetal;

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;
		std::shared_ptr<GameObject> ptrStart;
		std::shared_ptr<GameObject> ptrSavePoint;
		std::shared_ptr<GameObject> ptrGoal;
		std::shared_ptr<GameObject> ptrGoalSquareRed;
		std::shared_ptr<GameObject> ptrGoalSquareBlue;
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
					ptrGround = AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					isCreateMaagnets = false;
					break;

				case 1: //����N��
					AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 2: //����S��
					AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 3: //����
					ptrMoveMetal = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				case 4: //�����������
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), RIGHT_VEC, 3.5f);
					break;

				case 5: //�����������
					// position, Dir, Vol
					ptrMoveMetal = AddGameObject<MoveMetalObject>(Vec3(posX, -posY + m_CSVHeight, 0), UP_VEC, 3.5f);
					break;

				case 6://�󂹂��
					AddGameObject<BreakWall>(Vec3(posX, -posY + m_CSVHeight, 0), Vec3(0.0f));
					break;

				case 7://�{�^���������瓮����
					ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(7.5f, 0.9f, 0.9f), Vec3(posX + 4.7, -posY + m_CSVHeight , 0), LEFT_VEC);
					SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
					break;

				case 8://�����������p�{�^��
					ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(posX, -posY + m_CSVHeight-0.48, 0));
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
					isCreateMaagnets = false;
					break;

				case 15: //�S�[��
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + m_CSVHeight + 1, 0));
					ptrGoalSquareRed = AddGameObject<GoalSquareRed>(Vec3(1.0f) / size, Vec3(posX -1, -posY + m_CSVHeight + 7, 0));
					SetSharedGameObject(L"GoalSquareRed", ptrGoalSquareRed);
					ptrGoalSquareBlue = AddGameObject<GoalSquareBlue>(Vec3(1.0f) / size, Vec3(posX + 1, -posY + m_CSVHeight + 7, 0));
					SetSharedGameObject(L"GoalSquareBlue", ptrGoalSquareBlue);
					isCreateMaagnets = false;
					break;

				case 16: //���ԉE���
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_RIGHT, STATE_METAL, STATE_NONE); // ����2�ڂ�1���ƍ���]�A-1���ƉE��]
					break;

				case 17: //���ԍ����
					AddGameObject<GearObject>(Vec3(posX, -posY + m_CSVHeight, 0), ROT_LEFT, STATE_METAL, STATE_NONE); // ����2�ڂ�1���ƍ���]�A-1���ƉE��]
					break;

				case 18: //��
					AddGameObject<CoinObject>(Vec3(posX, -posY + m_CSVHeight, 0));
					break;

				default:
					break;
				}
			}
		}
	}

	void GameStage::OnUpdate()
	{
		m_InputHandler.PushHandler(GetThis<GameStage>());
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		if (PtrScene->GetGameState() == GameState::GameClear)
		{
			if (m_Clear <= false)
			{
				m_Clear = true;
				CreateAnimeSprite();
			}
			ClearResult();
		}
	}

	void GameStage::OnPushB()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrPlayer2 = GetSharedGameObject<Player2>(L"Player2");
		if (ptrPlayer->IsGoal() && ptrPlayer2->IsGoal()) {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			if (PtrScene->GetGameState() == GameState::GameClear)
				AddGameObject<FadeOut>(L"FADE_WHITE");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
			{
				m_pushButton = true;
				int ResultNum = PtrScene->GetResultNum();
				m_Lock = true;
				m_CntrolLock = true;
				int StageNum = PtrScene->GetStageNum();

				if (ResultNum == 0)
				{
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
				}
				if (ResultNum == 1)
				{
					StageNum++;
					PtrScene->SetStageNum(StageNum);
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
				if (ResultNum == 2)
				{
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
				}

			}
		}
	}
}
//end basecross
