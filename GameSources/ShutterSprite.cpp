/* !
@file TitleSprite.h
@brief �^�C�g���V�[���̔w�i�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	ShutterSprite::ShutterSprite(const shared_ptr<Stage>& stage, Vec3& Pos, wstring TextureKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth() / 2, (float)App::GetApp()->GetGameHeight())),
		m_Pos(Pos),
		m_textureKey(TextureKey)
	{
	}
	// �f�X�g���N�^
	ShutterSprite::~ShutterSprite() {}

	
}