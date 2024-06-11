/* !
@file FlashSprite.cpp
@brief �_�ł���UI
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FlashSprite::FlashSprite(const shared_ptr<Stage>& stage, const Vec3& position, const Vec2& defaultsize, const wstring& TextureKey, const bool& selected) :
		Flash(stage),
		m_FsPosition(position),
		m_defaultsize(defaultsize),
		m_texturekey(TextureKey),
		m_changeSpeed(false),
		m_Selected(selected),
		m_FlashType(Button)
	{
	}

	void FlashSprite::OnCreate()
	{
		Flash::CreateSprite(m_FsPosition, m_defaultsize, m_texturekey);	
		SetDrawLayer(11);
	}

	void FlashSprite::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (IsSelect())
		{
			if (pad.wPressedButtons & XINPUT_GAMEPAD_B && m_FlashType == Button)	
			{
				m_changeSpeed = true;	
			}

			Flash::UpdateFlashingSprite(2, 30, m_changeSpeed);
		}
		else
		{
			Flash::ResetColor();
		}
		Delete();
	}

	void FlashSprite::Delete()
	{
		auto PtrScene = App::GetApp()->GetScene<Scene>();

		if (PtrScene->GetGameState() == GameState::MainGame)
		{
			GetStage()->RemoveGameObject<FlashSprite>(GetThis<GameObject>());
		}
	}
}