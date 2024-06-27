#include "stdafx.h"
#include "Project.h"

#define PIDIV3 (XM_PIDIV4 * 1.5f) // π/2とπ/4の間

namespace basecross {
	void HammerPressArea::OnCreate()
	{
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(2.0f, 0.5f, 0.25f);
		m_TransComp->SetPosition(m_position.x, m_position.y - 0.25f, m_position.z-0.375f);
		
		m_ptrPlayerF = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_PlayerFScaleHelf = m_ptrPlayerF->GetComponent<Transform>()->GetScale() / 2;
		m_ptrPlayerS = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		m_PlayerSScaleHelf = m_ptrPlayerS->GetComponent<Transform>()->GetScale() / 2;

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		if(m_eMagPole == EState::eN)
		{
			m_DrawComp->SetTextureResource(L"REDAREA_TX");
		}
		if (m_eMagPole == EState::eS)
		{
			m_DrawComp->SetTextureResource(L"BULEAREA_TX");
		}
		if (m_eMagPole == EState::eFalse)
		{
			m_DrawComp->SetTextureResource(L"WHITEAREA_TX");
		}
		SetAlphaActive(true);
	}

	/** @brief Playerが範囲内にいるかを判定する関数(Player1用)
	*   @param 引数なし
	*   @return bool Playerが範囲内にいたらtrue
	*/
	bool HammerPressArea::AreaInPlayerF() {
		m_PlayerFPos = m_ptrPlayerF->GetComponent<Transform>()->GetWorldPosition();
		
		if (m_PlayerFPos.x <= m_AreaRightLimit && // プレイヤーがハンマーエリアの右より内側
			m_PlayerFPos.x >= m_AreaLeftLimit) // プレイヤーがハンマーエリアの左より内側
		{
			return true; // 内側なのでtrue
		}
		return false;
		
	}
	/** @brief Playerが範囲内にいるかを判定する関数(Player2用)
	*   @param 引数なし
	*   @return bool Playerが範囲内にいたらtrue
	*/
	bool HammerPressArea::AreaInPlayerS() {
		m_PlayerSPos = m_ptrPlayerS->GetComponent<Transform>()->GetWorldPosition();

		if (m_PlayerSPos.x <= m_AreaRightLimit && // プレイヤーがハンマーエリアの右より内側
			m_PlayerSPos.x >= m_AreaLeftLimit) // プレイヤーがハンマーエリアの左より内側
		{
			return true; // 内側なのでtrue
		}
		return false;

	}


	void HammerObject::OnCreate() {
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(m_Scale);
		m_position = m_CreatePos + m_posDiff;
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetPivot(0.0f, -m_PivotLength, 0.0f);
		m_TransComp->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		m_CollComp = AddComponent<CollisionObb>();
		m_CollComp->SetAfterCollision(AfterCollision::None);
		//m_CollComp->SetFixed(true);
		//m_CollComp->SetDrawActive(true);
		
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 0.3f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.75f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTBoneModelDraw>();
		switch (m_eMagPole)
		{
		case EState::eFalse:
			m_DrawComp->SetMeshResource(L"Hammer_Black_MESH");
			break;
		case EState::eN:
			m_DrawComp->SetMeshResource(L"Hammer_Red_MESH");
			break;
		case EState::eS:
			m_DrawComp->SetMeshResource(L"Hammer_Blue_MESH");
			break;
		case EState::eMetal:
			m_DrawComp->SetMeshResource(L"Hammer_Black_MESH");
			break;
		default:
			break;
		}
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		m_ptrPressArea = GetStage()->AddGameObject<HammerPressArea>(m_CreatePos, m_eMagPole);
		if (m_eMagPole != EState::eFalse) {
			m_MagArea = GetStage()->AddGameObject<MagnetArea>(Vec3(m_position.x, m_position.y, m_position.z + m_Scale.z / 2), m_MagAreaRadius);
		}

		m_ptrPlayerF = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_ptrPlayerS = GetStage()->GetSharedGameObject<Player2>(L"Player2");

		m_ptrAudio = App::GetApp()->GetXAudio2Manager();
	}

	void HammerObject::OnUpdate() {
		// ハンマーの動作切り替え
		switch (m_MoveState)
		{
		case HammerMoveState::Remove:
			RemoveHammer();
			break;

		case HammerMoveState::Stop:
			StopHammer(m_lastMoveState);
			break;

		case HammerMoveState::Antic:
			AnticHammer();
			break;

		case HammerMoveState::Swing:
			SwingHammer();
			break;

		default:
			break;
		}
			MagAreaCorrection();
	}

	// 巻き戻し
	void HammerObject::RemoveHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得
		
		auto rad = Utility::DegToRad(m_SwingVal);
		m_Rotation.x += delta * rad;
		m_TransComp->SetRotation(m_Rotation.x, 0.0f, 0.0f);

		if (m_Rotation.x >= 0.0f) { // ０度で止める
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Stop;
			SetStopTime(m_ResetStopTime);
		}
	}

	// 停止
	void HammerObject::StopHammer(const HammerMoveState& lastState) {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得
		m_CurrentTime += delta;

		if ((!isSEActive) && (m_lastMoveState == HammerMoveState::Swing))
		{
			m_ptrAudio->Start(L"HAMMER_SE", 0, 1.0f);
			isSEActive = true;
		}

		// 経過時間が設定した時間を越えたら
		if (m_CurrentTime >= m_StopTime)
		{
			ResetCurrentTime(); // 経過時間をリセット

			// 一個前の動作によって切り替え
			switch (m_lastMoveState)
			{
			// Remove(戻りなら)
			case HammerMoveState::Remove:
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Antic;// 予備動作へ
				break;

			// 停止の後に停止は無いのでbreak
			case HammerMoveState::Stop:
				break;

			// 予備動作の後に停止は無いのでbreak
			case HammerMoveState::Antic:
				break;

			// Swing(振り下ろしなら)
			case HammerMoveState::Swing:
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // 戻るへ
				break;

			default:
				break;
			}
			isSEActive = false;
		}
		return;
	}

	// 予備動作
	void HammerObject::AnticHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得

		m_CurrentTime += delta;

		if (m_CurrentTime <= 1.0f) // 1秒間
		{
			// 震わせる
			AnticTremble(delta);
		}
		else if (m_CurrentTime <= 2.0f) // １秒間
		{
			m_position = m_CreatePos + m_posDiff; // 初期位置に戻す
			m_TransComp->SetPosition(m_position);
			return; // 何もしない(一時停止)
		}
		else 
		{
			ResetCurrentTime();
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Swing; // 振り下ろしへ
			ChangeFixed(false);
		}
	}
	// 予備動作の振動
	void HammerObject::AnticTremble(const float& time) {

		// X座標が振れ幅の右端か左端なら
		if (m_position.x >= m_TrembleRightX || m_position.x <= m_TrembleLeftX) 
		{
			m_TrembleDir *= -1; // 正負反転
		}
		m_position.x += time * m_TrembleDir * m_TrembleSpeed;
		m_TransComp->SetPosition(m_position);
	}

	// 振り下ろし
	void HammerObject::SwingHammer() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得

		auto rad = Utility::DegToRad(m_SwingVal);
		m_Rotation.x -= delta * rad * m_SwingSpeed;
		m_TransComp->SetRotation(m_Rotation.x, 0.0f, 0.0f);

		// 約60度付近のとき
		if (m_Rotation.x <= -PIDIV3) {
			SwingingPlayerCheck();
		}
		if (m_Rotation.x <= -XM_PIDIV2) { // 90度で止める
			m_lastMoveState = m_MoveState;
			m_MoveState = HammerMoveState::Stop;
			SetStopTime(m_SwingStopTime);
			ChangeFixed(true);
		}
	}
	// 振り下ろしの時にPlayerがいたら
	void HammerObject::SwingingPlayerCheck(){
		if (m_ptrPressArea->AreaInPlayerF()) // エリア内にPlayer1がいるとき
		{
			int playerFMag = int(m_ptrPlayerF->GetPlayerMagPole());
			if (int(m_eMagPole) == playerFMag && playerFMag != STATE_NONE) { // 自分の磁極と範囲内のplayerの磁極が同じなら
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // 跳ね返し(戻る)
				SetStopTime(m_SwingStopTime * 1.5f); // 跳ね返した時のみ時間を1.5倍に
				ChangeFixed(true);
				return;
			}
		}

		if (m_ptrPressArea->AreaInPlayerS()) // エリア内にPlayer2がいるとき
		{
			int playerSMag = int(m_ptrPlayerS->GetPlayerMagPole());
			if (int(m_eMagPole) == playerSMag && playerSMag != STATE_NONE) { // 自分の磁極と範囲内のplayerの磁極が同じなら
				m_lastMoveState = m_MoveState;
				m_MoveState = HammerMoveState::Remove; // 跳ね返し(戻る)
				SetStopTime(m_SwingStopTime * 1.5f); // 跳ね返した時のみ時間を1.5倍に
				ChangeFixed(true);
				return;
			}
		}
	}

	// 振り下ろしたときにPlayerがいた時の接触判定
	void HammerObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrPlayerF = dynamic_pointer_cast<Player>(Other); // オブジェクト取得
		auto ptrPlayerS = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayerF) {
			m_ptrPlayerF->PlayerDeath();
		}
		if (ptrPlayerS) {
			m_ptrPlayerS->PlayerDeath();
		}
	}

	// 磁力エリアの位置補正
	void HammerObject::MagAreaCorrection() {

		// 磁極が無ければこれ以降は無視
		if (!m_MagArea) return;

		auto MagAreaTrans = m_MagArea->GetComponent<Transform>();
		Vec3 MagAreaPos = MagAreaTrans->GetWorldPosition();
		float diff = m_Rotation.x / XM_PIDIV2 * m_PivotLength;
		MagAreaTrans->SetPosition(MagAreaPos.x, m_position.y + diff, MagAreaPos.z);
	}
}