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
		//ptrColl->SetDrawActive(true);
		m_gravityComp = AddComponent<Gravity>();

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
		m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");
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

		int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
		if (scene == 1) {
			auto playerBanner = GetStage()->AddGameObject<PlayerBanner>(L"1P");
			auto m_playerBanner = playerBanner->GetComponent<Transform>();
			m_playerBanner->SetParent(GetThis<Player>());
		}

		AddTag(L"Player");
	}

	//更新処理
	void Player::OnUpdate() {
		if (!isGoal)
		{
			MovePlayer();
			ApplyForcePlayer();
		}
	}

	//プレイヤーの動き
	void Player::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// デルタタイムの取得
		m_pos = m_ptrTrans->GetWorldPosition();//プレイヤー座標の取得

		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (isCollRing) { // リングとの接触がある時(trueのとき)
			padLStick.y = pad.fThumbLY; // スティックのY軸も入力する
		}

		if (padLStick.length() > 0.0f) {
			m_pos = m_pos + padLStick * delta * m_speed;
		}
		if (m_speed != 5.0f) {
			m_pos = m_pos + delta * Vec3(m_speed, 0, 0) * (float)m_attribute;
		}


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

		if (padLStick.length() > 0.0f) {
			if (padLStick.x > 0.0f) {

			}
			else if (padLStick.x < 0.0f) {

			}
		}

		//ジャンプ処理
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				JumpPlayer();
				//jumpCount--;
			}
		}
		else if (isGround) {
			JumpCountReset();
		}

		if (m_pos.y < -10.0f) {
			auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
			float player2RespawnpPoint = ptrPlayer2->GetRespawnPoint();
			if (player2RespawnpPoint >= m_RespawnPoint) {
				ptrPlayer2->RespawnPlayer(m_RespawnPoint);
				RespawnPlayer(m_RespawnPoint);
			}
			else if (player2RespawnpPoint < m_RespawnPoint) {
				ptrPlayer2->RespawnPlayer(player2RespawnpPoint);
				RespawnPlayer(player2RespawnpPoint);
			}
		}

		//属性切り替え
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			//switch (m_eMagPole){
			//case EState::eFalse:
			//	m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");//N極
			//	m_eMagPole = EState::eN;
			//	break;
			//case EState::eN:
			//	m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");//S極
			//	m_eMagPole = EState::eS;
			//	break;
			//case EState::eS:
			//	m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
			//	m_eMagPole = EState::eFalse;
			//	break;
			//}
			switch (m_eMagPole) {
			case EState::eFalse:
				m_ptrDraw->SetMeshResource(L"PlayerRed_MESH");//N極
				m_eMagPole = EState::eN;
				break;
			case EState::eN:
				m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
				m_eMagPole = EState::eFalse;
				break;
			}

		}

		limitSpeed();
		m_pos += m_Velocity * delta;
		m_pos.z = 0.0f;
		m_ptrTrans->SetWorldPosition(Vec3(m_pos));

		if (length(m_inertia - m_pos) > 8.0f) {
			isInertia = false;
		}
		if (!isInertia) {
			m_Velocity.setAll(0);
		}
	}

	//ジャンプ関数
	void Player::JumpPlayer() {
		m_gravityComp = GetComponent<Gravity>();
		m_gravityComp->StartJump(m_gravityVelocity);
		Vec3 pos = GetComponent<Transform>()->GetWorldPosition();
		int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
		if (scene != 1) {
			GetStage()->AddGameObject<EffectPlayer>(pos, Vec3(0.3f), L"jump");
			App::GetApp()->GetXAudio2Manager()->Start(L"JUMP_SE", 0, 2.0f);
		}
		m_speed = 5.0f;
		m_attribute = 1;
	}

	//リスポーン地点を設定する
	void Player::SetRespawnPoint(shared_ptr<GameObject>& Other) {
		auto otherPos = Other->GetComponent<Transform>()->GetPosition();
		m_RespawnPoint = otherPos.x;
	}

	//リスポーンする
	void Player::RespawnPlayer(float respawnPoint) {
		m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
		m_eMagPole = EState::eFalse;
		m_pos = Vec3(respawnPoint + 2, 0.0f, 0.0f);
		m_ptrTrans->SetWorldPosition(Vec3(m_pos));
		isGoal = false;
		auto ptrSquareRed = GetStage()->GetSharedGameObject<GoalSquareRed>(L"GoalSquareRed");
		ptrSquareRed->ChangeTexture(L"TENNSENNRED_TX");
	}

	void Player::SetPlayerMagPole(int i) {
		switch (i) {
		case 1:
			m_eMagPole = EState::eN;
			break;
		case 2:
			m_eMagPole = EState::eS;
			break;
		default:
			m_eMagPole = EState::eFalse;
			break;
		}
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

		switch (m_currentMotion) {
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
	void Player::ApplyAttraction(shared_ptr<GameObject>& Other) {
		auto objPos = Other->GetComponent<Transform>()->GetWorldPosition();

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distanceTemp = m_direction.length();//sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

		auto playerToMagnet = m_direction.normalize();

		m_force = (playerToMagnet / m_distanceTemp) * ATTRACTION_CONSTANT * m_playerMass / (m_distanceTemp * m_distanceTemp);
		m_Velocity += m_force;
	}
	void Player::PlayerApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition();
		float objMass = 1.0f;
		float objAreaRadius = 3.0f;

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distance = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
		Vec3 force = (m_direction / m_distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force;
	}

	// プレイやーに斥力を適用
	void Player::ApplyRepulsion(shared_ptr<GameObject>& Other) {
		if (!isPlayerContact) {
			auto objPos = Other->GetComponent<Transform>()->GetWorldPosition();

			m_pos = m_ptrTrans->GetWorldPosition();

			m_direction = objPos - m_pos;
			m_distanceTemp = m_direction.length();//sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

			auto playerToMagnet = m_direction.normalize();

			m_force = (m_direction / m_distanceTemp) * ATTRACTION_CONSTANT * m_playerMass / (m_distanceTemp * m_distanceTemp);
			m_Velocity += m_force * -1;
			isInertia = true;
			m_inertia = objPos;

			int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
			if (scene != 1) {
				if (isJump) {
					GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(0.3f), L"jump");
					App::GetApp()->GetXAudio2Manager()->Start(L"JUMP_SE", 0, 2.0f);
					isJump = false;
				}
				if (length(objPos - m_pos) > 5.0f - 0.1f) {
					isJump = true;
				}
			}
		}
	}
	void Player::PlayerApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetWorldPosition();
		float objMass = 1.0f;

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distance = max(sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y), 1.0f);
		Vec3 force = (m_direction / m_distance) * REPEL_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force * -1;
	}

	void Player::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_ptrTrans->GetWorldPosition());
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < 3.0f) {
			if (playerMagPole < 0 || objMagPole < 0) {
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

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		m_pos = m_ptrTrans->GetWorldPosition();
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
		auto ptrGear = dynamic_pointer_cast<GearObject>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);
		auto ptrGround = dynamic_pointer_cast<GameObjectSample>(Other);
		auto ptrMoveFloor = dynamic_pointer_cast<MoveFloor>(Other);
		//auto magDir = GetMsgnetsDirection().second;
		if (ptrMoveMetal && (m_eMagPole != EState::eFalse)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMoveMetal);
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
		}
		if (ptrMetal && (m_eMagPole != EState::eFalse)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMetal);
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
		}
		if (ptrMagnetN && (m_eMagPole == EState::eS)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMagnetN);
			GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
			isEffect = true;
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"UNION_SE", 0, 2.0f);

		}
		if (ptrMagnetS && (m_eMagPole == EState::eN)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMagnetS);
			GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
			isEffect = true;
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"UNION_SE", 0, 2.0f);
		}
		if (ptrRing && (m_eMagPole != EState::eFalse)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrRing);
			isCollRing = true; //　リングについたからtrue
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
		}
		if (ptrPlayer2 && (m_eMagPole == EState::eN)) {
			int player2 = static_cast<int>(ptrPlayer2->GetPlayerMagPole());
			if (player2 == 2) {
				isPlayerContact = true;
			}
		}
		else {
			isPlayerContact = false;
		}
		if (ptrGear && (m_eMagPole != EState::eFalse) && (isCollGear == false)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrGear);
			isCollGear = true; //　歯車についたからtrue
			GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
		}
		if (ptrMoveFloor) {
			m_ptrTrans->SetParent(ptrMoveFloor);
		}
		if (ptrGround) {
			isGround = true;
			isEffect = true;
			isInertia = false;
		}

		// 着地の判定
		LandingJadge(Other);

		auto ptrBeltConLeft = dynamic_pointer_cast<BeltConveyorLeft>(Other);
		auto ptrBeltConRight = dynamic_pointer_cast<BeltConveyorRight>(Other);
		auto ptrBeltConSideLeft = dynamic_pointer_cast<BeltConveyorSideLeft>(Other);
		auto ptrBeltConSideRight = dynamic_pointer_cast<BeltConveyorSideRight>(Other);


		if (!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) {
			m_speed = 5.0f;
			m_attribute = 1;
		}

		if (ptrBeltConLeft) {
			Vec3 beltConLeftPos = ptrBeltConLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftPos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
			}
		}
		else if (ptrBeltConSideLeft) {
			Vec3 beltConLeftSidePos = ptrBeltConSideLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftSidePos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
			}
		}
		else if (ptrBeltConRight) {
			Vec3 beltConRightPos = ptrBeltConRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightPos.y < m_pos.y) {
				m_speed = 6.0f;
			}
		}
		else if (ptrBeltConSideRight) {
			Vec3 beltConRightSidePos = ptrBeltConSideRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightSidePos.y < m_pos.y) {
				m_speed = 6.0f;
			}
		}
		else if (!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) {
			m_speed = 5.0f;
			m_attribute = 1;
		}
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
		auto ptrGear = dynamic_pointer_cast<GearObject>(Other);
		if (ptrMoveMetal && (m_eMagPole == EState::eFalse)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
		if (ptrMetal && (m_eMagPole == EState::eFalse)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
		if (ptrMagnetN && (m_eMagPole != EState::eS)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
		if (ptrMagnetS && (m_eMagPole != EState::eN)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
		if (ptrRing && (m_eMagPole == EState::eFalse)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
		if (ptrGear && (m_eMagPole == EState::eFalse)) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
		auto ptrGear = dynamic_pointer_cast<GearObject>(Other);
		auto ptrGround = dynamic_pointer_cast<GameObjectSample>(Other);
		auto ptrMoveFloor = dynamic_pointer_cast<MoveFloor>(Other);
		if (ptrMoveMetal || ptrMetal || ptrMagnetN || ptrMagnetS || ptrRing || ptrGear || ptrMoveFloor) // チェック
		{
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
			//isCollRing = false; // リングから離れた時にfalse
		}

		if (ptrGround) {
			isGround = false;
		}

		auto ptrGoal = dynamic_pointer_cast<Goal>(Other);
		if (ptrGoal && m_pos.x > ptrGoal->GetComponent<Transform>()->GetPosition().x)
		{
			auto ptrSquareRed = GetStage()->GetSharedGameObject<GoalSquareRed>(L"GoalSquareRed");
			ptrSquareRed->ChangeTexture(L"RED_TX");
			AnimationPlayer(FRONT);
			isGoal = true;
		}

		auto ptrRespawnPoint = dynamic_pointer_cast<SavePoint>(Other);
		if (ptrRespawnPoint && m_pos.x > ptrRespawnPoint->GetComponent<Transform>()->GetPosition().x)
		{
			auto otherPos = Other->GetComponent<Transform>()->GetPosition();
			m_RespawnPoint = otherPos.x;
		}
	}

	// 速度を制限
	void Player::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (speed > MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * MAX_SPEED;
		}
	}


	void Player::OnUpdate2() {
		//wstring posStr(L"POS: ");
		//posStr += Util::FloatToWStr(m_pos.y);
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(posStr);

		//wstringstream wss;
		//wss << L"Player : " <<
		//	isPlayerContact << L", " << std::endl;
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(wss.str());

	}

}
//end basecross

