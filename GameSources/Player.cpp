#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(Vec3(1.0f));
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(true);
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.25f, 1.25f, 1.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		// BcPNTStaticModelDraw
		m_ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		//m_ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		//m_ptrDraw->SetMeshResource(L"Player01_MESH");
		m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw->AddAnimation(L"RIGHT", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"LEFT", 30, 30, true, 30);
		m_ptrDraw->AddAnimation(L"FRONT", 60, 30, true, 30);
		m_ptrDraw->AddAnimation(L"BACK", 90, 30, true, 30);
		//m_ptrDraw->ChangeCurrentAnimation(L"LEFT");

		//auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		//if (ptrCamera) {
		//	//カメラが追いかけるターゲット(プレイヤー)の設定
		//	ptrCamera->SetPlayerObj(GetThis<GameObject>());
		//}
		auto ptrCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//カメラが追いかけるターゲット(プレイヤー)の設定
			ptrCamera->SetPlayerObj(GetThis<GameObject>());
		}

		AddTag(L"Player");

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto EfkInterface = App::GetApp()->GetScene<Scene>()->GetEfkInterface();
		m_EffectStr = DataDir + L"Effects\\" + L"damage.efk";
		m_Effect = ObjectFactory::Create<EfkEffect>(EfkInterface, m_EffectStr);
	}

	//更新処理
	void Player::OnUpdate(){
		MovePlayer();
		//ApplyForcePlayer();
	}

	//プレイヤーの動き
	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// デルタタイムの取得
		Vec3 pos = m_ptrTrans->GetPosition();//プレイヤー座標の取得

		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (padLStick.length() > 0.0f) {
			pos = pos + padLStick * delta * m_speed;
		}
		m_ptrTrans->SetPosition(Vec3(pos));


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
			if (padLStick.x > 0.0f) {
				AnimationPlayer(RIGHT);
			}
			else if (padLStick.x < 0.0f) {
				AnimationPlayer(LEFT);
			}
		}
		else {
			AnimationPlayer(FRONT);
		}

		limitSpeed();
		pos += m_Velocity * delta;
		m_Velocity.setAll(0);


		m_ptrTrans->SetPosition(Vec3(pos));

		//ジャンプ処理
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				JumpPlayer();
				jumpCount--;
			}
		}
		else if (pos.y <= 5.0f) {
			jumpCount = 1;
		}

		if (pos.y < -5.0f) {
			DeathPlayer();
		}

		//属性切り替え
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			switch (m_eMagPole){
			case EState::eFalse:
				m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");//N極
				m_eMagPole = EState::eN;
				break;
			case EState::eN:
				m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");//S極
				m_eMagPole = EState::eS;
				break;
			case EState::eS:
				m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
				m_eMagPole = EState::eFalse;
				break;
			}
			
		}

	}

	//ジャンプ関数
	void Player::JumpPlayer() {
		auto gravity = GetComponent<Gravity>();
		gravity->StartJump(Vec3(0.0f, 11.0f, 0.0f));
		auto pos = GetComponent<Transform>()->GetPosition();
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_Effect, pos, Vec3(1.0f));
	}

	//死亡関数
	void Player::DeathPlayer() {
		PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	
	}

	//アニメーション関数
	void Player::AnimationPlayer(eMotion Motion) {

		//アニメーション変更
		m_currentMotion = Motion;

		// モーションのタイプが変わっていたら
		if (m_currentMotion != m_pastMotion || m_ptrDraw->GetCurrentAnimation() != m_motionKey.at(m_currentMotion))
		{
			// タイプに応じてモーションを変更する
			m_ptrDraw->ChangeCurrentAnimation(m_motionKey.at(m_currentMotion));
			m_pastMotion = m_currentMotion;
		}
		float delat = App::GetApp()->GetElapsedTime();

		switch (m_currentMotion){
		case RIGHT:
			m_ptrDraw->UpdateAnimation(delat * 1.0f);
			break;
		case LEFT:
			m_ptrDraw->UpdateAnimation(delat * 1.0f);
			break;
		default:
			m_ptrDraw->UpdateAnimation(delat * 0.0f);
			break;
		}
	}

	// プレイやーに引力を適用
	void Player::ApplyAttraction() {
		auto group = GetStage()->GetSharedObjectGroup(L"MagnetsObjects");
		auto groupVec = group->GetGroupVector();
		for (const auto& v : groupVec) {
			auto ptrMagObj = v.lock();
			auto objTrans = ptrMagObj->GetComponent<Transform>();
			Vec3 objPos = objTrans->GetPosition();
			//float objAreaRadius = ptrMagObj->GetAreaRadius();

			auto playerPos = m_ptrTrans->GetPosition();

			m_direction = objPos - playerPos;
			m_distanceTemp = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
			if (m_distanceTemp < m_distance) {
				m_distance = m_distanceTemp;
			}
		}
		m_force = (m_direction / m_distance) * ATTRACTION_CONSTANT * m_playerMass / (m_distance * m_distance);
		m_Velocity += m_force;
	}
	void Player::PlayerApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = 1.0f;
		float objAreaRadius = 3.0f;

		auto playerPos = m_ptrTrans->GetPosition();

		m_direction = objPos - playerPos;
		m_distance = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
		Vec3 force = (m_direction / m_distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force;
	}

	// プレイやーに斥力を適用
	void Player::ApplyRepulsion() {
		auto group = GetStage()->GetSharedObjectGroup(L"MagnetsObjects");
		auto groupVec = group->GetGroupVector();
		for (const auto& v : groupVec) {
			auto ptrMagObj = v.lock();
			auto objTrans = ptrMagObj->GetComponent<Transform>();
			Vec3 objPos = objTrans->GetPosition();
			//float objAreaRadius = ptrMagObj->GetAreaRadius();

			auto playerPos = m_ptrTrans->GetPosition();

			m_direction = objPos - playerPos;
			m_distanceTemp = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
			if (m_distanceTemp < m_distance) {
				m_distance = m_distanceTemp;
			}
		}
		m_force = (m_direction / m_distance) * REPEL_CONSTANT * m_playerMass / (m_distance * m_distance);
		m_Velocity += m_force * -1;
	}
	void Player::PlayerApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = 1.0f;

		auto playerPos = m_ptrTrans->GetPosition();

		m_direction = objPos - playerPos;
		m_distance = max(sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y), 1.0f);
		Vec3 force = (m_direction / m_distance) * REPEL_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force * -1;
	}

	void Player::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_ptrTrans->GetPosition());
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < 3.0f) {
			if (playerMagPole <  0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->PlayerApplyRepulsion();
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->PlayerApplyAttraction();
			}// ptrPlayer->ApplyAttraction();

		}
	}

	// 速度を制限
	void Player::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (speed > MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * MAX_SPEED;
		}
	}


	//void Player::OnUpdate2() {
	//	auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
	//	wstring fpsStr(L"FPS: ");
	//	fpsStr += Util::UintToWStr(fps);
	//	auto ptrString = GetComponent<StringSprite>();
	//	ptrString->SetText(fpsStr);
	//}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrBeltConLeft = dynamic_pointer_cast<BeltConveyorLeft>(Other);
		auto ptrBeltConRight = dynamic_pointer_cast<BeltConveyorRight>(Other);
		auto ptrBeltConSideLeft = dynamic_pointer_cast<BeltConveyorSideLeft>(Other);
		auto ptrBeltConSideRight = dynamic_pointer_cast<BeltConveyorSideRight>(Other);

		float delta = App::GetApp()->GetElapsedTime();// デルタタイムの取得

		Vec3 playerPos = m_ptrTrans->GetPosition();

		if (ptrBeltConLeft || ptrBeltConSideLeft) {
			playerPos = playerPos + Vec3(-0.5f, 0, 0) * delta * m_speed;
			m_ptrTrans->SetPosition(playerPos);
		}
		if (ptrBeltConRight || ptrBeltConSideRight) {
			playerPos = playerPos + Vec3(0.5f, 0, 0) * delta * m_speed;
			m_ptrTrans->SetPosition(playerPos);
		}
	}
}
//end basecross

