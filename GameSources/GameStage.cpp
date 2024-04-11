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
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
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

	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateObjGroup();

			AddGameObject<BackGroundSprite>();

			AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 4.0f, 0.0f));
			AddGameObject<BeltConveyorLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 4.0f, 0.0f));
			AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f, 1.0f, 1.0f), Vec3(3.0f, 4.0f, 0.0f));

			AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-3.0f, 2.0f, 0.0f));
			AddGameObject<BeltConveyorRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-2.0f, 2.0f, 0.0f));
			AddGameObject<BeltConveyorSideRight>(Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, 2.0f, 0.0f));

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			m_GameStageCsv.SetFileName(DataDir + L"TestMap6.csv");
			m_GameStageCsv.ReadCsv();

			CreateCsvObjects();

			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

						// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//�v���C���[�I�u�W�F�N�g��ǉ�
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

			// ���΃I�u�W�F�N�g��ǉ�
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateCsvObjects() {

		const auto& groundGroup = CreateSharedObjectGroup(L"Ground");
		const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

		float size = 1;
		Vec3 objScale = Vec3(1.0f) / size;

		std::shared_ptr<GameObject> ptrGround;
		std::shared_ptr<GameObject> ptrMag;


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
					ptrGround = AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY+5 , 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 1: //����N��
					ptrMag = AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 2: //����S��
					ptrMag = AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 3: //����
					ptrMag = AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//magnetsGroup->IntoGroup(ptrMag);
					break;

				case 9://�x���g�R���x�A�E���[
					AddGameObject<BeltConveyorSideRight>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 10://�x���g�R���x�A�E���^��
					AddGameObject<BeltConveyorRight>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 11://�x���g�R���x�A�����[
					AddGameObject<BeltConveyorSideLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 12://�x���g�R���x�A�����^��
					AddGameObject<BeltConveyorLeft>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					break;

				case 13: //�X�^�[�g
					ptrGround = AddGameObject<Start>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 14: //�Z�[�u�|�C���g
					ptrGround = AddGameObject<SavePoint>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				case 15: //�S�[��
					ptrGround = AddGameObject<Goal>(Vec3(1.0f) / size, Vec3(posX, -posY + 5, 0));
					//groundGroup->IntoGroup(ptrGround);
					isCreateMaagnets = false;
					break;

				default:
					break;
				}

				//if (isCreateMaagnets) {
				//	magnetsGroup->IntoGroup(ptrMag);
				//}
				//else {
				//	groundGroup->IntoGroup(ptrGround);
				//	isCreateMaagnets = true;
				//}
				//magnetsGroup->IntoGroup(ptrMag);
				//groundGroup->IntoGroup(ptrGround);


			}
		}
		magnetsGroup->IntoGroup(ptrMag);
		groundGroup->IntoGroup(ptrGround);

	}

}
//end basecross
