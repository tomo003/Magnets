/* !
@file ButtonUI.h
@brief タイトルシーンのスタートボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	ButtonSprite::ButtonSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(800.0f, 400.0f)),
		m_changeSpeed(false)
	{
	}
	// デストラクタ
	ButtonSprite::~ButtonSprite() {}

	// 初期化
	void ButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-400.0f, -50.0f, 0.0f), m_DefaultSize, L"BPUSH");	//位置座標、初期サイズ、ソース画像
	}

	// 更新処理
	void ButtonSprite::OnUpdate()
	{
		//ゲームパッドの取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)	//もしBボタンが押されたら
		{
			m_changeSpeed = true;	//点滅スピードの変更をtrueにする
		}

		Sprites::UpdateFlashingSprite(2, 30, m_changeSpeed);	//初期点滅スピード、変更後の点滅スピード
	}
}