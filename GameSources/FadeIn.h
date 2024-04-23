/*!
@file FadeIn.h
@brief �t�F�[�h�C���̒�`
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeIn : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

		wstring m_texKey; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey);
		// �f�X�g���N�^
		~FadeIn();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};
}
