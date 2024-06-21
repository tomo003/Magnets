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
	void PlayerMagTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -15.0f);
		const Vec3 at(0.0f,4.0f,0.0f);
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

	void PlayerMagTestStage::CreateObjGroup(){
		CreateSharedObjectGroup(L"BeltConveyorLeft");
		CreateSharedObjectGroup(L"BeltConveyorRight");
		CreateSharedObjectGroup(L"BeltConveyorSideLeft");
		CreateSharedObjectGroup(L"BeltConveyorSideRight");
	}

	void PlayerMagTestStage::OnCreate() {
		try {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene->SetGameState(GameState::MainGame);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateObjGroup();

			CreateBackGround(L"BACKGROUND4");

			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			AddGameObject<Block>(Vec3(10.0f, 1.0f, 1.0f), Vec3(0.0f, -3.0f, 0.0f), L"GROUND_TX");
			AddGameObject<Block>(Vec3(10.0f, 1.0f, 1.0f), Vec3(18.0f, -3.0f, 0.0f), L"GROUND_TX");
			AddGameObject<Block>(Vec3(10.0f, 1.0f, 1.0f), Vec3(-18.0f, -3.0f, 0.0f), L"GROUND_TX");

			//�v���C���[�I�u�W�F�N�g��ǉ�
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(3.0, 0.0f, 0.0f));
			SetSharedGameObject(L"Player2", ptrPlayer2);

			const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

			// ���΃I�u�W�F�N�g��ǉ�
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f));
			//ptrMagObj = AddGameObject<MagnetN>(Vec3(1.0f),Vec3(10.0f, -0.5f, 0.0f));

			//magnetsGroup->IntoGroup(ptrMagObj);

			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);
			//auto ptrMagObj = AddGameObject<MagnetsObject>(Vec3(3.5f, -0.5f, 0.0f), EState::eN);
			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

			// �������΃I�u�W�F�N�g��ǉ�
			//auto ptrMagObj = AddGameObject<MoveMetalObject>(Vec3(3.5f, 2.0f, 0.0f));
			//auto ptrMagObj = AddGameObject<RingObject>(Vec3(0.0f, 2.0f, 0.0f));

			AddGameObject<Metal>(Vec3(1.0f), Vec3(5.0f, 0.0f, 0.0f));

			AddGameObject<GearObject>(Vec3(-9.0f, 1.0f, 0.0f), ROT_LEFT, 50.0f, STATE_METAL, STATE_NONE);

			AddGameObject<BreakWall>(Vec3(17.0f, -2.0f, 0.0f), Vec3(0.0f));

			auto ptrMoveFloor = AddGameObject<MoveFloor>(Vec3(8.0f, 0.99f, 0.9f), Vec3(17.0f, -3.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"MoveFloor", ptrMoveFloor);
			auto ptrMoveFloorButton = AddGameObject <MoveFloorButton>(Vec3(15.0f, -2.5f, 0.0f));
			SetSharedGameObject(L"MoveFloorButton", ptrMoveFloorButton);
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
	void PlayerMagTestStage::CreateBackGround(const wstring& texkey) {
		for (int i = 0; i <= 5; i++) {
			AddGameObject<BackGroundSprite2>(Vec3(40, 30, 1.0f), Vec3(-50 + (40 * i), 0, 0), texkey);
		}
	}

}
//end basecross
