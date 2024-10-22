/*!
* @file MoveMagnetsObject.cpp
* @brief 移動式オブジェクトの実装
* @author 穴澤委也
* @details	往復する金属床
*			ボタンで動く床
*			↑用のボタン
*/

#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, true)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, true)
#define COL_PURPLE Col4(0.56f, 0.42f, 0.78f, true)

namespace basecross {
	//------------------------往復する金属オブジェクト------------------------------------------------
	void MoveMetalObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetTextureResource(L"METAL_TX");
		m_ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(2.0f, 0.75f, 0.75f);

		// 磁力エリアを追加
		m_ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius);
		auto m_AreaTransComp = m_ptrArea->GetComponent<Transform>();
		m_AreaTransComp->SetParent(GetThis<MoveMetalObject>()); // 親子関係を付ける
	}

	void MoveMetalObject::OnUpdate() 
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		// 開始地点と終了地点をセット
		const Vec3 start = m_points[m_currentPointIndex % m_points.size()];
		const Vec3 end = m_points[(m_currentPointIndex + 1) % m_points.size()];
		Vec3 pos = Utility::Lerp(start, end, m_ratio); // 線形補間関数
		m_ratio += m_speed * delta / (end - start).length(); // end - startは2点間を結ぶベクトル。その長さは「2点間の距離」となる
		if (m_ratio >= 1.0f)
		{
			m_currentPointIndex++;
			m_ratio = 0.0f;
		}

		//Vec3 pos = m_transform->GetPosition(); // 現在の座標を取得する
		m_ptrTrans->SetPosition(pos); // 新しい座標で更新する

		// プレイヤーに磁力を適用する処理を呼び出し
		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	// プレイヤーに磁力による力を適用(1P用)
	void MoveMetalObject::ApplyForcePlayer() 
	{
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		// プレイヤーとの距離が磁力範囲の半径以下なら
		if (distance < m_MagAreaRadius) {
			// プレイヤーの磁力がない時
			if (playerMagPole == -1) {
				return; // 何もしない
			}
			else { // プレイヤーに磁力があった場合
				ptrPlayer->ApplyAttration(GetThis<GameObject>()); // プレイヤー内の引力関数を呼び出し
				if (!ptrPlayer->IsAttrationState()) { // プレイヤーの引き寄せ状態のステートがfalseだったらtrueにする
					ptrPlayer->SetAttrationState(true);
				}
			}
		}
	}

	// プレイヤーに磁力による力を適用(2P用)
	void MoveMetalObject::ApplyForceSecondPlayer() 
	{
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		// プレイヤーとの距離が磁力範囲の半径以下なら
		if (distance < m_MagAreaRadius) {
			// プレイヤーの磁力がない時
			if (playerMagPole == -1) {
				return; // 何もしない
			}
			else { // プレイヤーに磁力があった場合
				ptrPlayer->ApplyAttration(GetThis<GameObject>()); // プレイヤー内の引力関数を呼び出し
				if (!ptrPlayer->IsAttrationState()) { // プレイヤーの引き寄せ状態のステートがfalseだったらtrueにする
					ptrPlayer->SetAttrationState(true);
				}
			}
		}
	}
	//------------------------------------------------------------------------------------------------

	//------------------------移動床用のスイッチ------------------------------------------------------
	void MoveFloorButton::OnCreate() 
	{
		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CYLINDER");
		m_DrawComp->SetTextureResource(L"MOVEFLOOR_TX");
		m_DrawComp->SetOwnShadowActive(true);
		//m_DrawComp->SetEmissive(Col4(0.0f, 1.0f, 0.0f, 1.0f));

		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(m_scale);

		//auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
		auto CollComp = AddComponent<CollisionObb>();
		//CollComp->AddExcludeCollisionGameObject(ptrMoveFloor);

		SetUp();
	}

	void MoveFloorButton::OnUpdate() 
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();
		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		m_TransComp->SetPosition(m_startPos.x, m_startPos.y, m_startPos.z); // 新しい座標で更新する

	}


	void MoveFloorButton::OnCollisionEnter(const CollisionPair& Pair) 
	{
		const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
		const Vec3& hitPoint = Pair.m_CalcHitPoint; // 衝突位置(Vec3)

		// 接触した相手が「Player」タグを持っていたら
		if (other->FindTag(L"Player")) {
			eMoveState = EMoveState::eMove;

			// 移動床のアクティブフラグをtrueにする(動かす)
			auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
			ptrMoveFloor->FloorActive(true);
		}
	}

	void MoveFloorButton::OnCollisionExit(const CollisionPair& Pair) 
	{
		const shared_ptr<GameObject>& other = Pair.m_Dest.lock()->GetGameObject();
		const Vec3& hitPoint = Pair.m_CalcHitPoint; // 衝突位置(Vec3)

		// 接触した相手が「Player」タグを持っていたら
		if (other->FindTag(L"Player")) {
			eMoveState = EMoveState::eTurnBack;

			 // 移動床のアクティブフラグをfalseにする(戻す・止める)
			auto ptrMoveFloor = GetStage()->GetSharedGameObject<MoveFloor>(L"MoveFloor");
			ptrMoveFloor->FloorActive(false);
		}
	}
	//-----------------------------------------------------------------------------------------------

	//------------------------移動床------------------------------------------------------------------
	void MoveFloor::OnCreate()
	{
		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		m_DrawComp->SetTextureResource(L"MOVEFLOOR_TX");
		m_DrawComp->SetOwnShadowActive(true);

		auto CollComp = AddComponent<CollisionObb>();
		CollComp->SetFixed(true);

		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(m_scale);

		m_actionComp = AddComponent<Action>();

		SetUp();
	}

	void MoveFloor::OnUpdate() 
	{
		// 初期位置、停止位置を越えるならステートを停止に切り替え
		if (eMoveState == EMoveState::eMove && m_position.x < m_endPos.x) {
			eMoveState = EMoveState::eStop;
		}
		if (eMoveState == EMoveState::eTurnBack && m_position.x > m_startPos.x)
		{
			eMoveState = EMoveState::eStop;
		}
		FloorMovePattern();
	}

	/**
	* @fn void FloorMovePattern()
	* @brief 移動床の状態に従って動作切り替えする関数
	* @param 引数なし
	* @return 戻り値なし
	* @details eMoveState(移動床の状態)によって動作を切り替え、位置を更新する
	*/
	void MoveFloor::FloorMovePattern() 
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();
		// デルタタイム(前フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		// 移動床の状態に従って動作切り替え
		switch (eMoveState)
		{
		case EMoveState::eTurnBack: // ReMoveなら戻る
			m_position -= m_MoveDir * m_speed * delta;
			if (!MoveSEPlay) // 稼働音がなってないなら鳴らす
			{
				m_kadouonn = XAPtr->Start(L"OPERATION_SE", 0, 2.0f);
				MoveSEPlay = true;
			}
			break;

		case EMoveState::eStop: // Stopなら停止(何も加算しない)
			XAPtr->Stop(m_kadouonn); // 稼働音を止めて
			MoveSEPlay = false; // 稼働音のフラグをfalseにする
			break;

		case EMoveState::eMove: // Moveなら移動
			m_position += m_MoveDir * m_speed * delta;
			if (!MoveSEPlay)// 稼働音がなってないなら鳴らす
			{
				m_kadouonn = XAPtr->Start(L"OPERATION_SE", 0, 2.0f);
				MoveSEPlay = true;
			}
			break;

		default:
			break;
		}
		m_TransComp->SetPosition(m_position); // 新しい座標で更新する

	}

	// プレイヤーが死亡した時に移動床を初期位置に戻す関数
	void MoveFloor::ResetAll() 
	{
		m_TransComp->SetPosition(m_startPos);
	}
	//------------------------------------------------------------------------------------------------
}