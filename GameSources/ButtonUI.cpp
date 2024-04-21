/* !
@file ButtonUI.h
@brief �^�C�g���V�[���̃X�^�[�g�{�^���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	ButtonSprite::ButtonSprite(const shared_ptr<Stage>& stage, const Vec3& pos, const wstring& texkey) :
		Sprites(stage),
		m_pos(pos),
		m_texkey(texkey),
		m_DefaultSize(Vec2(800.0f, 400.0f)),
		m_changeSpeed(false)
	{
	}
	// �f�X�g���N�^
	ButtonSprite::~ButtonSprite() {}

	// ������
	void ButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(m_pos, m_DefaultSize, m_texkey);	//�ʒu���W�A�����T�C�Y�A�\�[�X�摜
	}

	// �X�V����
	void ButtonSprite::OnUpdate()
	{
		//�Q�[���p�b�h�̎擾
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)	//����B�{�^���������ꂽ��
		{
			m_changeSpeed = true;	//�_�ŃX�s�[�h�̕ύX��true�ɂ���
		}

		Sprites::UpdateFlashingSprite(2, 30, m_changeSpeed);	//�����_�ŃX�s�[�h�A�ύX��̓_�ŃX�s�[�h
	}
}