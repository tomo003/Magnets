/*!
@file FadeOut.cpp
@brief �t�F�[�h�A�E�g�̒�`
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeOut : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

		wstring m_texKey; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey);
		// �f�X�g���N�^
		~FadeOut();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

	};
}
