/*!
@file GameObjectSample.cpp
@brief CSVファイル読み込み確認用仮オブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//ステージの通常ブロックの仮設置
	GameObjectSample::GameObjectSample(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	GameObjectSample::~GameObjectSample(){}

	void GameObjectSample::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		drawComp->SetTextureResource(L"CONCRETE_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	//ステージのN極マグネットプロックの仮設置
	MagnetN::MagnetN(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
		//const int State
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
		//m_State(State)
	{
	}
	MagnetN::~MagnetN() {}

	void MagnetN::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		drawComp->SetTextureResource(L"MGNETN_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		//switch (m_State)
		//{
		//case 1:
		//	m_eMagPole = EState::eN;
		//	drawComp->SetTextureResource(L"MGNETN_TX");
		//	break;
		//case 2:
		//	m_eMagPole = EState::eS;
		//	drawComp->SetTextureResource(L"MGNETS_TX");
		//	break;
		//default:
		//	break;
		//}
		m_eMagPole = EState::eN;

		//auto magnetsGroup = GetStage()->GetSharedObjectGroup(L"MagnetsObjects");
		//magnetsGroup->IntoGroup(GetThis<MagnetN>());

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
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

		if (distance < m_MagAreaRadius) {
			if (playerMagPole < 0 || objMagPole < 0) {
				return;
			}
			else if (playerMagPole == objMagPole) {
				ptrPlayer->ApplyRepulsion(GetThis<GameObject>());
			}
			else if (playerMagPole != objMagPole) {
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttraction();

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
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttraction();

		}
	}



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
		//drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		drawComp->SetTextureResource(L"MGNETS_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eS;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
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
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttraction();

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
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}// ptrPlayer->ApplyAttraction();

		}
	}

	//ステージの鉄ブロックの仮設置
	Metal::Metal(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	Metal::~Metal() {}

	void Metal::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		drawComp->SetTextureResource(L"METAL_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eMetal;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
	}

	void Metal::OnUpdate()
	{
		ApplyForcePlayer();
		ApplyForceSecondPlayer();
	}

	void Metal::ApplyForcePlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == -1) {
				return;
			}
			else {
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}
		}
	}
	void Metal::ApplyForceSecondPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		Vec3 playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		int playerMagPole = static_cast<int>(ptrPlayer->GetPlayerMagPole());
		int objMagPole = static_cast<int>(m_eMagPole);

		auto direction = ABSV(playerPos, m_Position);
		float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

		if (distance < m_MagAreaRadius) {
			if (playerMagPole == -1) {
				return;
			}
			else {
				ptrPlayer->ApplyAttraction(GetThis<GameObject>());
			}
		}
	}

	//ステージのスタートオブジェクトの仮設置
	Start::Start(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	Start::~Start() {}

	void Start::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		drawComp->SetTextureResource(L"START_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		ptrPlayer->GetComponent<Transform>()->SetPosition(m_Position.x, 0.0f, 0.0f);
		ptrPlayer->SetRespawnPoint(GetThis<GameObject>());
	}

	//ステージのゴールオブジェクトの仮設置
	Goal::Goal(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	Goal::~Goal() {}

	void Goal::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		drawComp->SetTextureResource(L"GOAL_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		AddTag(L"Goal");
	}

	//ステージのリスポーン地点の仮設置
	SavePoint::SavePoint(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SavePoint::~SavePoint() {}

	void SavePoint::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		drawComp->SetTextureResource(L"SAVEPOINT_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		AddTag(L"SavePoint");
	}
}
