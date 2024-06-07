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
		drawComp->SetTextureResource(L"CONCRETE_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	//テクスチャが変更できる四角いオブジェクト
	ChangeTextureBox::ChangeTextureBox(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	ChangeTextureBox::~ChangeTextureBox() {}

	void ChangeTextureBox::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	void ChangeTextureBox::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetTextureResource(Texture);
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

		//auto magnetsGroup = GetStage()->GetSharedObjectGroup(L"MagnetsObjects");
		//magnetsGroup->IntoGroup(GetThis<MagnetN>());

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius);
		ptrArea->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
		//m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.5f), L"MagneticRange");
		//m_efk->SetDrawLayer(-1);

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
		//m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.5f), L"MagneticRange");
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

	//void MagnetS::EfkStop(){
	//	m_efk->StopEffect();
	//}
	//void MagnetS::OnDestroy() {
	//	EfkStop();
	//}

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
		drawComp->SetTextureResource(L"METAL_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eMetal;

		auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius);
		ptrArea->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
		//m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.0f), L"MagneticRange");
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

	//void Metal::EfkStop() {
	//	m_efk->StopEffect();
	//}
	//void Metal::OnDestroy() {
	//	EfkStop();
	//}

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

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		auto ptrCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//カメラにスタートオブジェクト設定
			ptrCamera->SetStartObj(GetThis<GameObject>());
		}
	}

}
