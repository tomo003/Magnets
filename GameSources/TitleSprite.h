/* !
@file TitleSprite.h
@brief �^�C�g���V�[���̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TitleSprite : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

	public:
		// �R���X�g���N�^
		TitleSprite(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~TitleSprite();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����

	};
}