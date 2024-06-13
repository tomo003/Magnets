#include "stdafx.h"
#include "Project.h"

namespace basecross {

	// コリジョン判定範囲
	const AABB DEFF_AABB(Vec3(-100.0f, -100.0f, -100.0f), Vec3(100.0f, 100.0f, 100.0f));

	void Player::OnCreate()
	{
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_Scale);
		m_ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		m_ptrTrans->SetPosition(0.0f, 0.0f, 0.0f);
		m_ptrColl = AddComponent<CollisionObb>();
		//m_ptrColl->SetDrawActive(true);
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
		m_ptrDraw->SetMeshResource(L"PlayerRedanger_MESH");
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
		//if (scene != 0) {
			m_playerBanner = GetStage()->AddGameObject<PlayerBanner>(L"1P");
			m_playerBanner->GetComponent<Transform>()->SetParent(GetThis<Player>());
		//}


		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"PlayerRedanger_MESH");
		ptrShadow->SetDrawActive(true);

		AddTag(L"Player");
	}

	//更新処理
	void Player::OnUpdate() {
		if (!isGoal)
		{
			MovePlayer();
			ApplyForcePlayer();
			PlayerLimit();

			// y座標が-10以下になると死亡(リスポーン)
			if (m_pos.y < -10.0f) {
				PlayerDeath();
			}

			// コリジョン判定範囲をプレイヤーの座標から求めて設定
			auto collManager = m_ptrColl->GetCollisionManager();
			AABB root = AABB(DEFF_AABB.m_Min + m_pos, DEFF_AABB.m_Max + m_pos);
			collManager->SetRootAABB(root);
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
		if (m_speed > 5.0f) {
			m_pos = m_pos + delta * Vec3(m_speed, 0, 0) * (float)m_attribute;
		}
		if (m_speed > 5.0f && padLStick.x > 0.0f && !isLeftLimit && !isRightLimit) {
			m_pos = m_pos + padLStick * delta * Vec3(2.0f, 0, 0);
		}
		else if (m_speed > 5.0f && padLStick.x < 0.0f && !isLeftLimit && !isRightLimit) {
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
		else if (isGround) {
			JumpCountReset();
		}

		//属性切り替え
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			switch (m_eMagPole) {
			case EState::eFalse:
				m_ptrDraw->SetMeshResource(L"PlayerRedanger_MESH");//N極
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
		m_ptrTrans->SetRotation(Vec3(0));

		if (length(m_inertia - m_pos) > 8.0f) {
			isInertia = false;
		}
		if (!isInertia) {
			m_Velocity.setAll(0);
		}

		if (!isEffect) {
			if (length(m_objPos - m_pos) >= 1.5f) {
				isEffect = true;
			}
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

	void Player::PlayerDeath() {
		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 player2RespawnpPoint = ptrPlayer2->GetRespawnPoint();
		if (player2RespawnpPoint.x >= m_RespawnPoint.x) {
			ptrPlayer2->SetRespawnPoint(m_RespawnPoint);
			ptrPlayer2->RespawnPlayer();
			RespawnPlayer();
		}
		else if (player2RespawnpPoint.x < m_RespawnPoint.x) {
			SetRespawnPoint(player2RespawnpPoint);
			ptrPlayer2->RespawnPlayer();
			RespawnPlayer();
		}
	}

	//リスポーン地点を設定する
	void Player::SetRespawnPoint(shared_ptr<GameObject>& Other) {
		auto otherPos = Other->GetComponent<Transform>()->GetPosition();
		m_RespawnPoint = otherPos;
	}

	void Player::SetRespawnPoint(Vec3 RespawnPoint) {
		m_RespawnPoint = RespawnPoint;
	}

	//リスポーンする
	void Player::RespawnPlayer() {
		m_ptrDraw->SetMeshResource(L"PlayerBrack_MESH");//無極
		m_eMagPole = EState::eFalse;
		m_pos = Vec3(m_RespawnPoint.x + 2, m_RespawnPoint.y, 0.0f);
		m_ptrTrans->SetWorldPosition(Vec3(m_pos));
		auto ptrGoal = GetStage()->GetSharedGameObject<Goal>(L"Goal");
		ptrGoal->GoalReset();
		isGoal = false;
		auto ptrSquareRed = GetStage()->GetSharedGameObject<GoalSquareRed>(L"GoalSquareRed", false);
		if (!ptrSquareRed) return;
		ptrSquareRed->ChangeTexture(L"TENNSENNRED_TX");
		auto savePointGroup = GetStage()->GetSharedObjectGroup(L"SavePoint");
		auto groupVector = savePointGroup->GetGroupVector();
		for (auto v : groupVector)
		{
			auto ptrSavePoint = dynamic_pointer_cast<SavePoint>(v.lock());
			ptrSavePoint->ResetTexture();
		}
	}

	//プレイヤーが離れすぎないようにする制限
	void Player::PlayerLimit() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();//コントローラー座標の取得
		auto pad = device.GetControlerVec()[0];
		Vec3 padLStick(pad.fThumbLX, 0.0f, 0.0f);

		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		auto player2Pos = ptrPlayer2->GetComponent<Transform>()->GetWorldPosition();
		m_pos = m_ptrTrans->GetWorldPosition();

		auto direction = abs(m_pos.x - player2Pos.x);

		//プレイヤーが右に一定距離離れた時
		if (direction > m_limit && m_pos.x > player2Pos.x && padLStick.x >= 0)
		{
			m_speed = 0;
			isRightLimit = true;
		}
		//左に入力があったら
		else if ((padLStick.x < 0 && m_pos.x > player2Pos.x) || direction < m_limit)
		{
			isRightLimit = false;
			if (!isBelt)
			{
				m_speed = 5;
			}
			else
			{
				m_speed = 6;
			}
		}
		//プレイヤーが左に一定距離離れた時
		if (direction > m_limit && m_pos.x < player2Pos.x && padLStick.x <= 0)
		{
			m_speed = 0;
			isLeftLimit = true;
		}
		//右に入力があったら
		else if ((padLStick.x > 0 && m_pos.x < player2Pos.x) || direction < m_limit)
		{
			isLeftLimit = false;
			if (!isBelt)
			{
				m_speed = 5;
			}
			else
			{
				m_speed = 6;
			}
		}

		//m_ptrTrans->SetWorldPosition(Vec3(m_pos));
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

	void Player::PlayerBannerPosition(Vec3 position) {
		m_playerBanner->GetComponent<Transform>()->SetPosition(Vec3(position));
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

		m_force = (m_direction / m_distanceTemp) * ATTRACTION_CONSTANT * m_playerMass / (m_distanceTemp * m_distanceTemp);
		m_Velocity += m_force;

		isAttration = true;
	}
	void Player::PlayerApplyAttraction() {
		auto ptrMagObj = GetStage()->GetSharedGameObject<Player2>(L"Player2");
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
	void Player::ApplyRepulsion(shared_ptr<GameObject>& Other) {
		if (!isPlayerContact) {
			auto objPos = Other->GetComponent<Transform>()->GetWorldPosition();

			m_pos = m_ptrTrans->GetWorldPosition();

			m_direction = objPos - m_pos;
			m_distanceTemp = m_direction.length();//sqrtf(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

			m_force = (m_direction / m_distanceTemp) * ATTRACTION_CONSTANT * m_playerMass / (m_distanceTemp * m_distanceTemp);
			m_Velocity += m_force * -1;
			isInertia = true;
			m_inertia = objPos;
			isRepulsion = true;

			int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
			if (scene != 1) {
				if (isJump) {
					GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(0.3f), L"jump");
					App::GetApp()->GetXAudio2Manager()->Start(L"JUMP_SE", 0, 2.0f);
					isJump = false;
				}
				if (length(objPos - m_pos) > 3.0f - 0.1f) {
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
		auto ptrGearFloor = dynamic_pointer_cast<GearObjFloor>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
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
				m_objPos = ptrMoveMetal->GetComponent<Transform>()->GetPosition();
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
			m_emState = magneticState::emMetal;
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
			m_emState = magneticState::emMetal;
		}
		if (ptrMagnetN && (m_eMagPole == EState::eS)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMagnetN);
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				m_objPos = ptrMagnetN->GetComponent<Transform>()->GetPosition();
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
			m_emState = magneticState::emMagnet;
		}
		if (ptrMagnetS && (m_eMagPole == EState::eN)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrMagnetS);
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				m_objPos = ptrMagnetS->GetComponent<Transform>()->GetPosition();
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
			m_emState = magneticState::emMagnet;
		}
		if (ptrRing && (m_eMagPole != EState::eFalse)) {
			m_gravityComp->SetGravityZero();
			m_ptrTrans->SetParent(ptrRing);
			isCollRing = true; //　リングについたからtrue
			if (isEffect) {
				GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
				isEffect = false;
				m_objPos = ptrRing->GetComponent<Transform>()->GetPosition();
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"UNION_SE", 0, 2.0f);
			}
			m_emState = magneticState::emRing;
		}
		if (ptrPlayer2) {
			isPlayerContact = true;
		}
		if (ptrPlayer2 && (m_eMagPole == EState::eN)) {
				isPlayerContact = true;
				m_emState = magneticState::emPlayer;
		}

		int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
		if (ptrPlayer2) {
			if (ptrPlayer2->GetComponent<Transform>()->GetPosition().y > m_pos.y + 0.5f) {
				m_playerBanner->GetComponent<Transform>()->SetPosition(0, 2.0f, 0);
				ptrPlayer2->PlayerBannerPosition(Vec3(0, 2.5f, 0));
			}
		}

		if (ptrMoveFloor) {
			m_ptrTrans->SetParent(ptrMoveFloor);
		}
		if (ptrGround) {
			isGround = true;
			isEffect = true;
			isInertia = false;
			isRepulsion = false;
			isAttration = false;
		}

		// 着地の判定
		LandingJadge(Other);

		auto ptrBeltConLeft = dynamic_pointer_cast<BeltConveyorLeft>(Other);
		auto ptrBeltConRight = dynamic_pointer_cast<BeltConveyorRight>(Other);
		auto ptrBeltConSideLeft = dynamic_pointer_cast<BeltConveyorSideLeft>(Other);
		auto ptrBeltConSideRight = dynamic_pointer_cast<BeltConveyorSideRight>(Other);


		if ((!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) && !isRightLimit && !isLeftLimit) {
			m_speed = 5.0f;
			m_attribute = 1;
			isBelt = false;
		}

		if (ptrBeltConLeft && !isLeftLimit) {
			Vec3 beltConLeftPos = ptrBeltConLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftPos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
				isBelt = true;
			}
		}
		else if (ptrBeltConSideLeft && !isLeftLimit) {
			Vec3 beltConLeftSidePos = ptrBeltConSideLeft->GetComponent<Transform>()->GetPosition();
			if (beltConLeftSidePos.y < m_pos.y) {
				m_speed = 6.0f;
				m_attribute = -1;
				isBelt = true;
			}
		}
		else if (ptrBeltConRight && !isRightLimit) {
			Vec3 beltConRightPos = ptrBeltConRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightPos.y < m_pos.y) {
				m_speed = 6.0f;
				isBelt = true;
			}
		}
		else if (ptrBeltConSideRight && !isRightLimit) {
			Vec3 beltConRightSidePos = ptrBeltConSideRight->GetComponent<Transform>()->GetPosition();
			if (beltConRightSidePos.y < m_pos.y) {
				m_speed = 6.0f;
				isBelt = true;
			}
		}
		else if ((!ptrBeltConLeft || !ptrBeltConSideLeft || !ptrBeltConRight || !ptrBeltConSideRight) && !isRightLimit && !isLeftLimit) {
			m_speed = 5.0f;
			m_attribute = 1;
			isBelt = false;
		}

		if (ptrGearFloor) {
			isGearFloor = true;
			auto GearFloorPos = ptrGearFloor->GetComponent<Transform>()->GetWorldPosition();
			if (m_eMagPole == EState::eN) {
				m_gravityComp->SetGravityZero();
				m_ptrTrans->SetParent(ptrGearFloor);
				if (isEffect && isAttration) {
					GetStage()->AddGameObject<EffectPlayer>(m_pos, Vec3(1.0f), L"impact");
					isEffect = false;
					m_objPos = ptrGearFloor->GetComponent<Transform>()->GetWorldPosition();
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"UNION_SE", 0, 2.0f);
				}
			}
			if (m_eMagPole == EState::eFalse && (m_pos.y > 0.5f + GearFloorPos.y)) {
				m_ptrTrans->SetParent(ptrGearFloor);
			}
			
		}
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
		auto ptrGearFloor = dynamic_pointer_cast<GearObjFloor>(Other);
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
			if (ptrGearFloor) {
				auto GearFloorPos = ptrGearFloor->GetComponent<Transform>()->GetWorldPosition();
				if (m_eMagPole == EState::eFalse) {
					m_gravityComp->SetGravity(m_gravity);
					m_gravityComp->SetGravityVerocityZero();
				}
				if (GearFloorPos.y + m_Scale.y / 2 > m_pos.y) {
					m_ptrTrans->ClearParent();
				}
			}
			m_emState = magneticState::emNone;

			auto ptrPlayer2= dynamic_pointer_cast<Player2>(Other);
			if (ptrPlayer2){
				isPlayerContact = true;
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) {
		auto ptrMoveMetal = dynamic_pointer_cast<MoveMetalObject>(Other); // オブジェクト取得
		auto ptrMetal = dynamic_pointer_cast<Metal>(Other);
		auto ptrMagnetN = dynamic_pointer_cast<MagnetN>(Other);
		auto ptrMagnetS = dynamic_pointer_cast<MagnetS>(Other);
		auto ptrRing = dynamic_pointer_cast<RingObject>(Other);
		auto ptrGearFloor = dynamic_pointer_cast<GearObjFloor>(Other);
		//auto ptrGround = dynamic_pointer_cast<GameObjectSample>(Other);
		auto ptrMoveFloor = dynamic_pointer_cast<MoveFloor>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);
		if (ptrMoveMetal || ptrMetal || ptrMagnetN || ptrMagnetS || ptrRing || ptrMoveFloor) // チェック
		{
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
			m_emState = magneticState::emNone;
			isAttration = false;
		}
		if (ptrGearFloor) {
			m_gravityComp->SetGravity(m_gravity);
			m_gravityComp->SetGravityVerocityZero();
			m_ptrTrans->ClearParent();
			isGearFloor = false;
		}

		if (ptrMoveMetal && (m_eMagPole != EState::eFalse)) {
			m_objPos = ptrMoveMetal->GetComponent<Transform>()->GetPosition();
		}

		if (ptrPlayer2) {
			int scene = App::GetApp()->GetScene<Scene>()->GetSecen();
			if (scene != 1) {
				m_playerBanner->GetComponent<Transform>()->SetPosition(Vec3(0, 1.5f, 0));
			}
			isPlayerContact = false;
		}


		isGround = false;

		auto ptrGoal = dynamic_pointer_cast<Goal>(Other);
		if (ptrGoal && m_pos.x > ptrGoal->GetComponent<Transform>()->GetPosition().x && !isGoal)
		{
			auto ptrSquareRed = GetStage()->GetSharedGameObject<GoalSquareRed>(L"GoalSquareRed");
			ptrSquareRed->ChangeTexture(L"RED_TX");
			AnimationPlayer(FRONT);
			isGoal = true;
		}

		auto ptrRespawnPoint = dynamic_pointer_cast<SavePoint>(Other);
		if (ptrRespawnPoint && m_pos.x > ptrRespawnPoint->GetComponent<Transform>()->GetPosition().x && m_RespawnPoint.x < ptrRespawnPoint->GetComponent<Transform>()->GetPosition().x)
		{
			auto otherPos = Other->GetComponent<Transform>()->GetPosition();
			m_RespawnPoint = otherPos;
		}
	}

	// 速度を制限
	void Player::limitSpeed() {
		float speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
		if (!isPlayerContact)
		{
			if (speed > MAX_SPEED) {
				m_Velocity = (m_Velocity / speed) * MAX_SPEED;
			}
		}
		//プレイヤー同士が触れているときの速度制限を変更する
		else if (speed > LIMIT_MAX_SPEED) {
			m_Velocity = (m_Velocity / speed) * LIMIT_MAX_SPEED;
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

