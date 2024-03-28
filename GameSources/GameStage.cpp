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
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//wstring strMap = DataDir + L"Maps";

			m_GameStageCsv.SetFileName(DataDir + L"TestMap1.csv");
			m_GameStageCsv.ReadCsv();

			CreateCsvObjects();

			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			//AddGameObject<Ground>(Vec3(1),Vec3(0));

			//�v���C���[�I�u�W�F�N�g��ǉ�
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

			// ���΃I�u�W�F�N�g��ǉ�
			auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			SetSharedGameObject(L"MagnetsObject", ptrMagObj);


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateCsvObjects() {

		//const auto& groundGroup = CreateSharedObjectGroup(L"Ground");

		float size = 5;
		Vec3 objScale = Vec3(1.0f) / size;

		auto& LineVec = m_GameStageCsv.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				float posX = (float)((int)j -10) / size;
				float posY = (float)((int)i) / size;

				//�ʏ�n��
				if (Tokens[j] == L"0") {
					AddGameObject<GameObjectSample>(Vec3(1.0f) / size, Vec3(posX, -posY - 3.0f, 0));
				}
				//����
				if (Tokens[j] == L"1") {
					AddGameObject<Metal>(Vec3(1.0f) / size, Vec3(posX, -posY , 0));
				}
				//����N��
				if (Tokens[j] == L"2") {
					AddGameObject<MagnetN>(Vec3(1.0f) / size, Vec3(posX, -posY , 0));
				}
				//����S��
				if (Tokens[j] == L"3") {
					AddGameObject<MagnetS>(Vec3(1.0f) / size, Vec3(posX, -posY , 0));
				}
			}
		}
	}

}
//end basecross
