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

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius);
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

	// プレイヤーに磁力による力を適用
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
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
			}

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
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
			}// ptrPlayer->ApplyAttration();

		}
	}

	//ステージのN極マグネットプロックの仮設置
	MagnetN::MagnetN(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	MagnetN::~MagnetN() {}

	void MagnetN::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"MGNETN_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eN;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius);
		ptrArea->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
	}

	void MagnetN::OnUpdate()
	{
		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void MagnetN::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		//プレイヤーが一定の距離に入ったら
		if (distance < m_MagAreaRadius) {
			//属性がない同士だったら
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			//同じ属性だったら
			else if (playerMagPole == objMagPole) {
				//斥力の呼び出し
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			//違う属性だったら
			else if (playerMagPole != objMagPole) {
				//引力の呼び出し
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttration();

		}
	}
	void MagnetN::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}

		}
	}

	void MagnetN::MoveMagnetArea(const Vec3 pos) {
		m_ptrArea->AddComponent<Transform>()->SetPosition(pos);
	}

	//void MagnetN::EfkStop() {
	//	m_efk->StopEffect();
	//}
	//void MagnetN::OnDestroy() {
	//	EfkStop();
	//}


	//ステージのS極マグネットプロックの仮設置
	MagnetS::MagnetS(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	MagnetS::~MagnetS() {}

	void MagnetS::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"MGNETS_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eS;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius);
		ptrArea->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
	}

	void MagnetS::OnUpdate()
	{
		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void MagnetS::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetWorldPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttration();

		}
	}
	void MagnetS::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttration(GetThis<GameObject>());
			}

		}
	}

	void MagnetS::MoveMagnetArea(const Vec3 pos) {
		m_ptrArea->AddComponent<Transform>()->SetPosition(pos);
	}
}
//end basecross

