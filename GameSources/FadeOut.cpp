/* !
@file FadeOut.cpp
@brief �t�F�[�h�A�E�g�̎���
@prod �F�� �S�I
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	FadeOut::FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight())),
		m_texKey(texKey)
	{
	}
	// �f�X�g���N�^
	FadeOut::~FadeOut() {}
	// �����܂�

	// ������
	void FadeOut::OnCreate()
	{
		// �����l�̐ݒ�(�c�A�����A��)
		Sprites::CreateFadeSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, m_texKey, FadeType::FadeOut);
	}

	// �X�V����
	void FadeOut::OnUpdate()
	{
		Sprites::UpdateFadeSprite(1.0f);
	}
}