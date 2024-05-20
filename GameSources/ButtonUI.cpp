/* !
@file ButtonUI.h
@brief タイトルシーンのスタートボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	ButtonSprite::ButtonSprite(const shared_ptr<Stage>& stage, const Vec3& pos, const wstring& texkey) :
		Sprites(stage),
		m_pos(pos),
		m_texkey(texkey),
		m_DefaultSize(Vec2(800.0f, 600.0f)),
		m_changeSpeed(false)
	{
	}
	// デストラクタ
	ButtonSprite::~ButtonSprite() {}

	// 初期化
	void ButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(m_pos, m_DefaultSize, m_texkey);	//位置座標、初期サイズ、ソース画像
	}

	// 更新処理
	void ButtonSprite::OnUpdate()
	{
		//ゲームパッドの取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];

		auto scene = app->GetScene<Scene>()->GetSecen();
		if (scene == 0 || scene == 2) {
			if (pad.wPressedButtons & XINPUT_GAMEPAD_B || pad2.wPressedButtons & XINPUT_GAMEPAD_B)
			{
				m_changeSpeed = true;	//点滅スピードの変更をtrueにする
			}
		}
		if (scene == 1) {
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || pad2.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				m_changeSpeed = true;	//点滅スピードの変更をtrueにする
			}
		}

		Sprites::UpdateFlashingSprite(2, 30, m_changeSpeed);	//初期点滅スピード、変更後の点滅スピード
	}
}