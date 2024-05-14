/*!
@file GameObjectSample.cpp
@brief CSV�t�@�C���ǂݍ��݊m�F�p���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�X�e�[�W�̒ʏ�u���b�N�̉��ݒu
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

	//�X�e�[�W��N�Ƀ}�O�l�b�g�v���b�N�̉��ݒu
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
		GetStage()->AddGameObject<EffectPlayer>(m_Position, Vec3(1.0f), L"MagneticRange");

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



	//�X�e�[�W��S�Ƀ}�O�l�b�g�v���b�N�̉��ݒu
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
		GetStage()->AddGameObject<EffectPlayer>(m_Position, Vec3(1.0f), L"MagneticRange");
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

	//�X�e�[�W�̓S�u���b�N�̉��ݒu
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

	//�X�e�[�W�̃X�^�[�g�I�u�W�F�N�g�̉��ݒu
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
		//drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		//drawComp->SetTextureResource(L"START_TX");

		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		ptrPlayer->GetComponent<Transform>()->SetPosition(m_Position.x, 0.0f, 0.0f);
		ptrPlayer->SetRespawnPoint(GetThis<GameObject>());

		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		ptrPlayer2->GetComponent<Transform>()->SetPosition(m_Position.x, 2.0f, 0.0f);
		ptrPlayer2->SetRespawnPoint(GetThis<GameObject>());
	}

	//�X�e�[�W�̃S�[���I�u�W�F�N�g�̉��ݒu
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
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.3f, 0.3f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"RingObject_MESH");
		//drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		drawComp->SetTextureResource(L"GOAL_TX");
		drawComp->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale.x ,m_Scale.y + 1 ,m_Scale.z/2);
		transComp->SetRotation(0.0f, XM_PIDIV2 , 0.0f);

		SetAlphaActive(true);

		AddTag(L"Goal");

		//GetStage()->AddGameObject<Sprites>()->CreateSprite(Vec3(0.0f, 0.0f, 0.0f), Vec2(200, 200), L"TENNSENN_TEX");
	}

	void Goal::OnUpdate()
	{
		if (isCollPlayer && isCollPlayer2)
		{
			PlayerGoal();
		}

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Position);
	}

	void Goal::PlayerGoal()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];

		if (!isDisplaySprite)
		{
			GetStage()->AddGameObject<Sprites>()->CreateSprite(Vec3(-400.0f, 250.0f, 0.0f), Vec2(800, 130), L"CLEAR");
			GetStage()->AddGameObject<ButtonSprite>(Vec3(-400.0f, -50.0f, 0.0f), L"BPUSH");
			isDisplaySprite = true;
		}
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		ptrCamera->ZoomCamera();
		
		//auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		//ptrDuoCamera->ZoomCamera();

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B || pad2.wPressedButtons & XINPUT_GAMEPAD_B) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	void Goal::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		wstringstream wss;
		wss << L"Player : " <<
			 L", " << std::endl;
		auto scene = App::GetApp()->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(wss.str());

		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayer && m_Position.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x) {
			isCollPlayer = true;
		}
		if (ptrPlayer2 && m_Position.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x) {
			isCollPlayer2 = true;
		}
	}

	//�X�e�[�W�̃��X�|�[���n�_�̉��ݒu
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
