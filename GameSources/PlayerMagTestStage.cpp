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



	void PlayerMagTestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// �n�ʂ̃I�u�W�F�N�g��ǉ�
			AddGameObject<Ground>(Vec3(50.0f, 1.0f, 1.0f), Vec3(0.0f, -1.5f, 0.0f));

			//�v���C���[�I�u�W�F�N�g��ǉ�
			auto ptrPlayer = AddGameObject<Player>();
			SetSharedGameObject(L"Player", ptrPlayer);
			auto ptrPlayer2 = AddGameObject<Player2>();
			SetSharedGameObject(L"Player2", ptrPlayer2);

			const auto& magnetsGroup = CreateSharedObjectGroup(L"MagnetsObjects");

			// ���΃I�u�W�F�N�g��ǉ�
			auto ptrMagObj = AddGameObject<MagnetN>(Vec3(1.0f), Vec3(3.5f, -0.5f, 0.0f));
			//ptrMagObj = AddGameObject<MagnetN>(Vec3(1.0f),Vec3(10.0f, -0.5f, 0.0f));

			magnetsGroup->IntoGroup(ptrMagObj);

			//SetSharedGameObject(L"MagnetsObject", ptrMagObj);

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
