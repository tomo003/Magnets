/*!
@file title.cpp
@brief �^�C�g�����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -5.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleStage::CreateTitleSprite() {

		AddGameObject<TitleSprite>();
		AddGameObject<ButtonSprite>();

	} 

	void TitleStage::PlayBGM() {
		//m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"TITLESTAGE_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	}


	void TitleStage::OnCreate() {
		CreateViewLight();
		CreateTitleSprite();
		PlayBGM();
	}

	void TitleStage::OnDestroy(){
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}


	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {
			if (!stage) {
				PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				//XAPtr->Start(L"SELECT_SE", 0, 0.5f);
				stage = true;
			}
		}
	}
}
//end basecross
