/* !
@file TitleSprite.h
@brief �^�C�g���V�[���̔w�i�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	TitleSprite::TitleSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// �f�X�g���N�^
	TitleSprite::~TitleSprite() {}

	// ������
	void TitleSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"TITLE");
	}

	// �X�V����
	void TitleSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}