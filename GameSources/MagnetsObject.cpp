#include "stdafx.h"
#include "Project.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, true)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, true)
#define COL_PURPLE Col4(0.56f, 0.42f, 0.78f, true)

namespace basecross {
	void MagnetsObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetEmissive(COL_RED);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(Vec3(0.75f));

		m_eMagPole = EState::eN;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");
	}

	void MagnetsObject::OnUpdate(){
		auto& app = App::GetApp();
		auto KeyState = app->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			switch(m_eMagPole) {
			case EState::eN :
				m_eMagPole = EState::eS;
				m_ptrDraw->SetEmissive(COL_BLUE);
				break;

			case EState::eS :
				m_eMagPole = EState::eN;
				m_ptrDraw->SetEmissive(COL_RED);
				break;

			case EState::eFalse :
				m_eMagPole = EState::eN;
				m_ptrDraw->SetEmissive(COL_RED);
				break;
			};
		}
		if (KeyState.m_bPressedKeyTbl['G']) {
			m_eMagPole = EState::eFalse;
			m_ptrDraw->SetEmissive(COL_PURPLE);
		}

		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void MagnetsObject::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if(playerMagPole == objMagPole){
				ptrPlayer->ApplyRepulsion();
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttraction();
			}// ptrPlayer->ApplyAttraction();

		}
	}
	void MagnetsObject::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if(playerMagPole == objMagPole){
				ptrPlayer->ApplyRepulsion();
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttraction();
			}// ptrPlayer->ApplyAttraction();

		}
	}
}
//end basecross

