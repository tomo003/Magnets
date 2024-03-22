#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1.0f, 1.0f, 1.0f);
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		// BcPNTStaticModelDraw
		m_ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		m_ptrDraw->SetMeshResource(L"Player01_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		//auto gravityComp = AddComponent<Gravity>();
	}

	void Player::OnUpdate(){
		MovePlayer();
	}

	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// デルタタイムの取得
		Vec3 pos = m_ptrTrans->GetPosition();//プレイヤー座標の取得

		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		//auto KeyState = app->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPushKeyTbl['A']) {
		//	padLStick.x = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['D']) {
		//	padLStick.x = 1.0f;
		//}
		//else {
		//	padLStick.x = 0;
		//}


		if (padLStick.length() > 0.0f) {
			pos = pos + padLStick * delta * speed;
		}
		m_ptrTrans->SetPosition(Vec3(pos));

		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				JumpPlayer();
				jumpCount--;
			}
		}
		else if (pos.y <= -0.4f) {
			jumpCount = 1;
		}

	}

	void Player::JumpPlayer() {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(Vec3(0.0f, 5.0f, 0.0f));
	}

	// プレイやーに引力を適用
	//void applyAttraction() {
	//	Vec2 direction = other.position - position;
	//	float distance = std::max(std::sqrt(direction.x * direction.x + direction.y * direction.y), 1.0f);
	//	sf::Vector2f force = (direction / distance) * GRAVITY_CONSTANT * mass * other.mass / (distance * distance);
	//	velocity += force;
	//}
}
//end basecross

