/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W�̎���
@author �����I
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
		AddGameObject<BackGroundSprite2>(Vec3(95, 60, 1.0f), Vec3(0, 0, 50), L"BACKGROUND1");
		
		AddGameObject<TitleSprite>();
		//�{�^���X�v���C�g�̓X�^���o�C�V�[���ł��g�p���Ă���ۂ��̂ō��W�ς�����A�X�^���o�C�V�[����UI�ʒu���ς��
		AddGameObject<ButtonSprite>(Vec3( - 400.0f, 50.0f, 0.0f), L"BPUSH");

	} 

	//void TitleStage::PlayBGM() {
	//	m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	//}


	void TitleStage::OnCreate() {
		CreateViewLight();
		CreateTitleSprite();
		//�V���b�^�[�X�v���C�gS�i�j�ɂ̐���
		m_sFade = AddGameObject<ShutterSprite>(Vec3(780, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"SFADE");
		//�V���b�^�[�X�v���C�gN�i�ԁj�ɂ̐���
		m_nFade = AddGameObject<ShutterSprite>(Vec3(-1610, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"NFADE");
		//PlayBGM();

		m_ptrSprite = AddGameObject<Sprites>();
		Vec2 Size = Vec2(App::GetApp()->GetGameWidth(), App::GetApp()->GetGameHeight());
		m_ptrSprite->CreateSprite(Vec3(-Size.x / 2, Size.y / 2, 0.0f), Size, L"FADE_WHITE");
		m_diffuseColor = Col4(1.0f, 1.0f, 1.0f, 0.0f);
		m_ptrSpriteDraw = m_ptrSprite->GetComponent<PCTSpriteDraw>();
		m_ptrSpriteDraw->SetDiffuse(m_diffuseColor);
		
	}

	void TitleStage::OnDestroy(){
	}

	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];
		const Vec3& mLPos = m_nFade->GetPosition();
		const Vec3& mRPos = m_sFade->GetPosition();
		auto delta = app->GetElapsedTime();

		m_CurrentTime += delta; // �o�ߎ��Ԃ��J�E���g
		 // �o�ߎ��Ԃ����[�r�[�ɑJ�ڂ���܂ł̎��Ԉȏゾ������
		if (m_CurrentTime >= m_ToMovieTime && !isFadeOut)
		{
			isFadeOut = true; // �t�F�[�h�A�E�g��true
		}
		if (isFadeOut) // �t�F�[�h�A�E�g��true�Ȃ�
		{
			m_diffuseColor.w += delta / m_FadeTime; // �����x���t�F�[�h�ɂ����鎞��(1�b)��1.0�ɂȂ�悤�ɉ��Z
			m_ptrSpriteDraw->SetDiffuse(m_diffuseColor); // �F���Z�b�g
			if (m_diffuseColor.w >= 1.0f) // �����x��1.0�ȏ�ɂȂ�����
			{
				// ���[�r�[�X�e�[�W�ɑJ��
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMovieStage");
			}
		}

		//�^�C�g���V�[����B�{�^������
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {

			if (!stage) {
				//�X�^���o�C�V�[���Ɉڍs
				PostEvent(1.5f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				//���艹
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				//�V���b�^�[���܂鉹
				XAPtr->Start(L"SHUTTER_SE", 0, 5.0f);
				//�V�[���ڍs���̃V���b�^�[�e�N�X�`���p�̃t���O
				stage = true;
			}
		}

		if (stage)
		{
			//�E���ɏo������S�Ƀe�N�X�`����X���W��-20���傫�����
			if (mRPos.x > -20.0f)
			{
				//S�Ƀe�N�X�`����X���}�C�i�X����Ĉړ�
				m_sFade->SetPosition(mRPos - Vec3(delta * 1550.0f, 0.0f, 0.0f));
			}
			//���܂ōs������ړ����~�܂�
			else
			{
				m_sFade->SetPosition(Vec3(-20.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
			//�E���ɏo������S�Ƀe�N�X�`����X���W��-810��菬����������
			if (mLPos.x < -810.0f)
			{
				//N�Ƀe�N�X�`����X���v���X����Ĉړ�
				m_nFade->SetPosition(mLPos - Vec3(-delta * 1550.0f, 0.0f, 0.0f));
			}
			//���܂ōs������ړ����~�܂�
			else
			{
				m_nFade->SetPosition(Vec3(-810.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
		}
	}
}
//end basecross
