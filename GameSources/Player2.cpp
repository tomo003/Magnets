#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player2::OnCreate()
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
		m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");
		m_ptrDraw->SetMeshToTransformMatrix(spanMat);

		m_ptrDraw->AddAnimation(L"RIGHT", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"LEFT", 30, 30, true, 30);
		m_ptrDraw->AddAnimation(L"FRONT", 60, 30, true, 30);
		m_ptrDraw->AddAnimation(L"BACK", 90, 30, true, 30);
		//m_ptrDraw->ChangeCurrentAnimation(L"LEFT");

		auto ptrCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//カメラが追いかけるターゲット(プレイヤー)の設定
			ptrCamera->SetSecondPlayerObj(GetThis<GameObject>());
		}
		
		int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
		if (scene != 0) {
			auto playerBanner = GetStage()->AddGameObject<PlayerBanner>(L"2P");
			auto m_playerBanner = playerBanner->GetComponent<Transform>();
			m_playerBanner->SetParent(GetThis<Player2>());
		}
		AddTag(L"Player2");
		AddTag(L"Player");
	}

	//更新処理
	void Player2::OnUpdate() {
		if (!isGoal)
		{
			MovePlayer();
			ApplyForcePlayer();
			PlayerLimit();
		}
	}

	//プレイヤーの動き
	void Player2::MovePlayer() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();// デルタタイムの取得
		m_pos = m_ptrTrans->GetWorldPosition();//プレイヤー座標の取得

		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[1];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		if (padLStick.length() > 0.0f) {
			m_pos = m_pos + padLStick * delta * m_speed;
		}
		if (m_speed > 5.0f) {
			m_pos = m_pos + delta * Vec3(m_speed, 0, 0) * (float)m_attribute;
		}
		if (m_speed > 5.0f && padLStick.x > 0.0f && !isLimit) {
			m_pos = m_pos + padLStick * delta * Vec3(2.0f, 0, 0);
		}
		else if (m_speed > 5.0f && padLStick.x < 0.0f && !isLimit) {
			m_pos = m_pos + padLStick * delta * Vec3(2.0f, 0, 0);
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

		//ジャンプ処理
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			if (jumpCount > 0) {
				//JumpPlayer();
				//jumpCount--;
			}
		}
		else if (m_pos.y <= 5.0f) {
			jumpCount = 1;
		}

		if (m_pos.y < -10.0f) {
			auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
			float playerRespawnpPoint = ptrPlayer->GetRespawnPoint();
			if (playerRespawnpPoint >= m_RespawnPoint) {
				ptrPlayer->SetRespawnPoint(m_RespawnPoint);
				ptrPlayer->RespawnPlayer();
				RespawnPlayer();
			}
			else if (playerRespawnpPoint < m_RespawnPoint) {
				m_RespawnPoint = playerRespawnpPoint;
				ptrPlayer->RespawnPlayer();
				RespawnPlayer();
			}
		}

		//属性切り替え
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			//switch (m_eMagPole) {
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
				m_ptrDraw->SetMeshResource(L"PlayerBlue_MESH");//S極
				m_eMagPole = EState::eS;
				break;
			case EState::eS:
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

		if (!isEffect) {
			if (length(m_objPos - m_pos) >= 2.0f) {
				isEffect = true;
			}
		}
	}

	//ジャンプ関数
	void Player2::JumpPlayer() {
		m_gravityComp = GetComponent<Gravity>();
		m_gravityComp->StartJump(m_gravityVelocity);
		Vec3 pos = GetComponent<Transform>()->GetWorldPosition();
		int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
		if (scene != 1) {
			GetStage()->AddGameObject<EffectPlayer>(pos, Vec3(0.3f), L"jump");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"JUMP_SE", 0, 2.0f);
		}
		m_speed = 5.0f;
		m_attribute = 1;
	}

	//リスポーン地点を設定する
	void Player2::SetRespawnPoint(shared_ptr<GameObject>& Other) {
		auto otherPos = Other->GetComponent<Transform>()->GetPosition();
		m_RespawnPoint = otherPos.x;
	}

	void Player2::SetRespawnPoint(float RespawnPoint) {
		m_RespawnPoint = RespawnPoint;
	}

	//リスポーンする
	void Player2::RespawnPlayer() {
		m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
		m_eMagPole = EState::eFalse;
		m_pos = Vec3(m_RespawnPoint +1 , 0.0f, 0.0f);
		m_ptrTrans->SetWorldPosition(Vec3(m_pos));
		isGoal = false;
		auto ptrSquareBlue = GetStage()->GetSharedGameObject<GoalSquareBlue>(L"GoalSquareBlue");
		ptrSquareBlue->ChangeTexture(L"TENNSENNBLUE_TX");
		auto savePointGroup = GetStage()->GetSharedObjectGroup(L"SavePoint");
		auto groupVector = savePointGroup->GetGroupVector();
		for (auto v : groupVector)
		{
			auto ptrSavePoint = dynamic_pointer_cast<SavePoint>(v.lock());
			ptrSavePoint->ResetTexture();
		}
	}

	//プレイヤーが離れすぎないようにする制限
	void Player2::PlayerLimit() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		m_pos = m_ptrTrans->GetWorldPosition();

		auto direction = abs(m_pos.x - playerPos.x);

		//プレイヤーが右に一定距離離れた時
		if (direction > m_limit && m_pos.x > playerPos.x && padLStick.x >= 0)
		{
			m_speed = 0;
			isLimit = true;
		}
		//左に入力があったら
		else if (padLStick.x < 0 && m_pos.x > playerPos.x)
		{
			m_speed = 5;
			isLimit = false;
		}
		//プレイヤーが左に一定距離離れた時
		if (direction > m_limit && m_pos.x < playerPos.x && padLStick.x <= 0)
		{
			m_speed = 0;
			isLimit = true;
		}
		//右に入力があったら
		else if (padLStick.x > 0 && m_pos.x < playerPos.x)
		{
			m_speed = 5;
			isLimit = false;
		}

		m_ptrTrans->SetWorldPosition(Vec3(m_pos));
	}

	//アニメーション関数
	void Player2::AnimationPlayer(eMotion Motion) {

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

	void Player2::SetPlayerMagPole(int i) {
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

	// プレイやーに引力を適用
	void Player2::ApplyAttraction(shared_ptr<GameObject>& Other) {
		auto objPos = Other->GetComponent<Transform>()->GetWorldPosition();

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distanceTemp = m_direction.length();//sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

		m_force = (m_direction / m_distanceTemp) * ATTRACTION_CONSTANT * m_playerMass / (m_distanceTemp * m_distanceTemp);
		m_Velocity += m_force;
	}
	void Player2::PlayerApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetWorldPosition();
		float objMass = 1.0f;
		float objAreaRadius = 3.0f;

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distance = sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
		Vec3 force = (m_direction / m_distance) * ATTRACTION_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force;
	}

	// プレイやーに斥力を適用
	void Player2::ApplyRepulsion(shared_ptr<GameObject>& Other) {
		if (!isPlayerContact) {
			auto objPos = Other->GetComponent<Transform>()->GetWorldPosition();

			m_pos = m_ptrTrans->GetWorldPosition();

			m_direction = objPos - m_pos;
			m_distanceTemp = m_direction.length();//sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
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
	void Player2::PlayerApplyRepulsion() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto objTrans = ptrMagObj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetWorldPosition();
		float objMass = 1.0f;

		m_pos = m_ptrTrans->GetWorldPosition();

		m_direction = objPos - m_pos;
		m_distance = max(sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y), 1.0f);
		Vec3 force = (m_direction / m_distance) * REPEL_CONSTANT * m_playerMass * objMass / (m_distance * m_distance);
		m_Velocity += force * -1;
	}

	void Player2::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
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

	void Player2::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		m_pos = m_ptrTrans->GetWorldPosition();
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrGround = dynamic_pointer_cast<GameObjectSample>(Other);
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
				m_objPos = ptrMetal->GetComponent<Transform>()->GetPosition();
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
		if (ptrPlayer) {
		isPlayerContact = true;
		}
		if (ptrPlayer && (m_eMagPole == EState::eS)) {
			isPlayerContact = true;
		}

		if (ptrGround) {
			isEffect = true;
			isGround = true;
			isInertia = false;
		}

		auto ptrBeltConLeft = dynamic_pointer_cast<BeltConveyorLeft>(Other);
		auto ptrBeltConRight = dynamic_pointer_cast<BeltConveyorRight>(Other);
		auto ptrBeltConSideLeft = dynamic_pointer_cast<BeltConveyorSideLeft>(Other);
		auto ptrBeltConSideRight = dynamic_pointer_cast<BeltConveyorSideRight>(Other);

		if ((!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) && !isLimit) {
			m_speed = 5.0f;
			m_attribute = 1;
		}

		if (ptrBeltConLeft && !isLimit) {
			Vec3 beltConLeftPos = ptrBeltConLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftPos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
			}
		}
		else if (ptrBeltConSideLeft && !isLimit) {
			Vec3 beltConLeftSidePos = ptrBeltConSideLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftSidePos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
			}
		}
		else if (ptrBeltConRight && !isLimit) {
			Vec3 beltConRightPos = ptrBeltConRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightPos.y < m_pos.y) {
				m_speed = 6.0f;
			}
		}
		else if (ptrBeltConSideRight && !isLimit) {
			Vec3 beltConRightSidePos = ptrBeltConSideRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightSidePos.y < m_pos.y) {
				m_speed = 6.0f;
			}
		}
		else if ((!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) && !isLimit) {
			m_speed = 5.0f;
			m_attribute = 1;
		}

	}

	void Player2::OnCollisionExcute(shared_ptr<GameObject>& Other) {
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

		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		if (ptrPlayer) {
			isPlayerContact = true;
		}
	}

	void Player2::OnCollisionExit(shared_ptr<GameObject>& Other) {
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrGear = dynamic_pointer_cast<GearObject>(Other);
		auto ptrGround = dynamic_pointer_cast<GameObjectSample>(Other);
		auto ptrMoveFloor = dynamic_pointer_cast<MoveFloor>(Other);
		if (ptrMoveMetal || ptrMetal || ptrMagnetN || ptrMagnetS ||  ptrGear || ptrMoveFloor) // チェック
		{
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
		}

		if (ptrMoveMetal && (m_eMagPole != EState::eFalse)) {
			m_objPos = ptrMoveMetal->GetComponent<Transform>()->GetPosition();
		}


		if (ptrGround) {
			isGround = false;
		}

		auto ptrGoal = dynamic_pointer_cast<Goal>(Other);
		if (ptrGoal && m_pos.x > ptrGoal->GetComponent<Transform>()->GetPosition().x && !isGoal)
		{
			auto ptrSquareBlue = GetStage()->GetSharedGameObject<GoalSquareBlue>(L"GoalSquareBlue");
			ptrSquareBlue->ChangeTexture(L"BLUE_TX");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
			AnimationPlayer(FRONT);
			isGoal = true;
		}

		auto ptrRespawnPoint = dynamic_pointer_cast<SavePoint>(Other);
		if (ptrRespawnPoint && m_pos.x > ptrRespawnPoint->GetComponent<Transform>()->GetPosition().x && m_RespawnPoint < ptrRespawnPoint->GetComponent<Transform>()->GetPosition().x)
		{
			auto otherPos = Other->GetComponent<Transform>()->GetPosition();
			m_RespawnPoint = otherPos.x;
		}

		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		if (ptrPlayer)
		{
			isPlayerContact = false;
		}
	}

	// 速度を制限
	void Player2::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (speed > MAX_SPEED && !isPlayerContact) {
			m_Velocity = (m_Velocity / speed) * MAX_SPEED;
		}
		else if (speed > LIMIT_MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * LIMIT_MAX_SPEED;
		}
	}


	void Player2::OnUpdate2() {
		//wstring posStr(L"POS: ");
		//posStr += Util::FloatToWStr(m_pos.y);
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(posStr);
	}

}
//end basecross
