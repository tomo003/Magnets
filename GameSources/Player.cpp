#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(0.3f));
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.4f, 0.0f)
		);

		// BcPNTStaticModelDraw
		m_ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		//m_ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		//m_ptrDraw->SetMeshResource(L"Player01_MESH");
		m_ptrDraw->SetMeshResource(L"PlayerMotionfbx_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw->AddAnimation(L"RIGHT", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"LEFT", 30, 60, true, 30);
		m_ptrDraw->AddAnimation(L"FRONT", 60, 90, true, 30);
		m_ptrDraw->AddAnimation(L"BACK", 90, 120, true, 30);
		m_ptrDraw->ChangeCurrentAnimation(L"LEFT");
	}

	void Player::OnUpdate(){
		MovePlayer();
		float delat = App::GetApp()->GetElapsedTime();
		m_ptrDraw->UpdateAnimation(delat);
		m_ptrDraw->GetCurrentAnimation();
	}

	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// �f���^�^�C���̎擾
		Vec3 pos = m_ptrTrans->GetPosition();//�v���C���[���W�̎擾

		auto device = app->GetInputDevice();//�R���g���[���[���W�̎擾
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

		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			count++;
			count = count % 3;
			switch (count){
			case 0:
				m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");
				break;
			case 1:
				m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");
				break;
			default:
				m_ptrDraw->SetMeshResource(L"PlayerMotionfbx_MESH");
				break;
			}
			
		}

	}

	void Player::JumpPlayer() {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(Vec3(0.0f, 5.0f, 0.0f));
	}

	// �v���C��[�Ɉ��͂�K�p
	//void applyAttraction() {
	//	Vec2 direction = other.position - position;
	//	float distance = std::max(std::sqrt(direction.x * direction.x + direction.y * direction.y), 1.0f);
	//	sf::Vector2f force = (direction / distance) * GRAVITY_CONSTANT * mass * other.mass / (distance * distance);
	//	velocity += force;
	//}
}
//end basecross

