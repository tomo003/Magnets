/*!
@file MovieStage.cpp
@brief �^�C�g�����[�r�[�𗬂�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W
	//--------------------------------------------------------------------------------------
	void TitleMovieStage::CreateViewLight() {
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

	// ����
	void TitleMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//���f�B�A�f�B���N�g�����擾
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"Movie\\";
		wstring strMovie = dataDir + L"MagnetsMOVIE.mp4";
		SetMovieFileName(strMovie);
		//�Đ�
		Play();

		// �t�F�[�h�A�E�g�p�̃X�v���C�g��p��
		m_ptrSprite = AddGameObject<Sprites>();
		Vec2 Size = Vec2(App::GetApp()->GetGameWidth(), App::GetApp()->GetGameHeight());
		m_ptrSprite->CreateSprite(Vec3(-Size.x / 2, Size.y / 2, 0.0f), Size, L"FADE_BLACK");
		m_ptrSpriteDraw = m_ptrSprite->GetComponent<PCTSpriteDraw>();
		m_ptrSpriteDraw->SetDiffuse(m_diffuseColor);
	}

	// �X�V
	void TitleMovieStage::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleMovieStage>());

		if (isFadeOut)
		{
			m_diffuseColor.w += delta / m_FadeTime; // �����x���t�F�[�h�ɂ����鎞��(1�b)��1.0�ɂȂ�悤�ɉ��Z
			m_ptrSpriteDraw->SetDiffuse(m_diffuseColor); // �F���Z�b�g
			if (m_diffuseColor.w >= 1.0f) // �����x��1.0�ȏ�ɂȂ�����
			{
				// �^�C�g���X�e�[�W�ɑJ��
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}
	}

	//�{�^��(�ǂ��ł�)
	void TitleMovieStage::OnPushAny() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//���艹
		XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
		// �t�F�[�h�A�E�g�t���O��true
		isFadeOut = true;
	}
}