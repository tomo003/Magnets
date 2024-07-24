/*!
* @file GearObject.cpp
* @brief 歯車オブジェクトの実装
* @author 穴澤委也
* @details	歯車オブジェクトの実装
*			歯車に付属している床オブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// -------------------------歯車に付属する床オブジェクト-----------------------
	// 生成
	void GearObject::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.1f),
			Vec3(0.0f),
			Vec3(0.0f),
			Vec3(0.0f)
		);

		m_DrawComp = AddComponent<PNTStaticDraw>();
		m_DrawComp->SetMeshResource(L"GearObject_MESH");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		m_TransComp = GetComponent<Transform>();
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);
		m_TransComp->SetScale(m_Scale);
		m_TransComp->SetRotation(m_Rotation);

		// 床を追加して親子付け
		m_ptrGearFloorF = GetStage()->AddGameObject<GearObjFloor>(Vec3(m_position.x, m_position.y + m_floorDiffY, 0.0f), m_RotSpeed, m_RotDir, m_eFloorStateF);
		m_ptrGearFloorF->GetComponent<Transform>()->SetParent(GetThis<GearObject>());
		m_ptrGearFloorS = GetStage()->AddGameObject<GearObjFloor>(Vec3(m_position.x, m_position.y - m_floorDiffY, 0.0f), m_RotSpeed, m_RotDir, m_eFloorStateS);
		m_ptrGearFloorS->GetComponent<Transform>()->SetParent(GetThis<GearObject>());

	}

	void GearObject::OnUpdate() {
		// 回転させる
		float delta = App::GetApp()->GetElapsedTime();
		m_Rotation.z += Utility::DegToRad(m_RotSpeed) * delta * m_RotDir;
		m_TransComp->SetRotation(m_Rotation);
	}
	// ----------------------------------------------------------------------------

	// -------------------------歯車に付属する床オブジェクト-----------------------
	// 生成
	void GearObjFloor::OnCreate() {
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		// 磁力の状態に応じてテクスチャ切り替え
		// 歯車の床は磁力が無いので金属or無極
		switch (m_eMagPole)
		{
		case EState::eFalse:
			m_ptrDraw->SetTextureResource(L"GROUND_TX");
			break;
		case EState::eMetal:
			m_ptrDraw->SetTextureResource(L"METAL_TX");
			break;
		default:
			break;
		}
		m_ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(m_Scale);

		if (m_eMagPole != EState::eFalse) {
			auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius);
			auto m_AreaTransComp = ptrArea->GetComponent<Transform>();
			m_AreaTransComp->SetParent(GetThis<GearObjFloor>());
		}
	}

	void GearObjFloor::OnUpdate() {
		RotToCenter();

		m_position = m_ptrTrans->GetWorldPosition();

		if (m_eMagPole != EState::eFalse) {
			ApplyForcePlayer();
			ApplyForceSecondPlayer();
		}
	}

	void GearObjFloor::RotToCenter() {
		// 親子付けしてると回転も親に影響されるため同じ回転量で親の反対向きに回す
		float delta = App::GetApp()->GetElapsedTime();
		m_Rotation.z -= Utility::DegToRad(m_RotSpeed) * delta * m_RotDir;
		if (m_Rotation.z <= -XM_2PI) {
			m_Rotation.z += XM_2PI;
		}//whileに
		m_ptrTrans->SetRotation(m_Rotation);
	}

	void GearObjFloor::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == STATE_NONE) {
				return;
			}
			else {
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
				if (!ptrPlayer->IsAttrationState()) {
					ptrPlayer->SetAttrationState(true);
				}
			}
		}
	}

	void GearObjFloor::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == STATE_NONE) {
				return;
			}
			else {
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
				if (!ptrPlayer->IsAttrationState()) {
					ptrPlayer->SetAttrationState(true);
				}
			}
		}
	}
	// ----------------------------------------------------------------------------
}