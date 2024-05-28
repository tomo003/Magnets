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

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
		m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.5f), L"MagneticRange");
		m_efk->SetDrawLayer(-1);

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


	void MagnetN::EfkStop() {
		m_efk->StopEffect();
	}
	void MagnetN::OnDestroy() {
		EfkStop();
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
		drawComp->SetTextureResource(L"MGNETS_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eS;

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
		m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.5f), L"MagneticRange");
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

	void MagnetS::EfkStop(){
		m_efk->StopEffect();
	}
	void MagnetS::OnDestroy() {
		EfkStop();
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
		drawComp->SetTextureResource(L"METAL_TX");
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		m_eMagPole = EState::eMetal;

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_Position, m_MagAreaRadius, L"TYPEALL_TX");
		m_efk = GetStage()->AddGameObject<EffectPlayer>(Vec3(m_Position.x, m_Position.y, m_Position.z + (m_Scale.z / 2)), Vec3(1.0f), L"MagneticRange");
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

	void Metal::EfkStop() {
		m_efk->StopEffect();
	}
	void Metal::OnDestroy() {
		EfkStop();
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

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		ptrPlayer->GetComponent<Transform>()->SetPosition(m_Position.x +1.0f , 0.0f, 0.0f);
		ptrPlayer->SetRespawnPoint(GetThis<GameObject>());

		auto ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		ptrPlayer2->GetComponent<Transform>()->SetPosition(m_Position.x, 0.0f, 0.0f);
		ptrPlayer2->SetRespawnPoint(GetThis<GameObject>());
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
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.7f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"RingObject_MESH");
		drawComp->SetTextureResource(L"RED_TX");
		drawComp->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale.x + 2, m_Scale.y + 7.5, m_Scale.z / (float)3);
		transComp->SetRotation(0.0f, XM_PIDIV2, 0.0f);

		SetAlphaActive(true);

		AddTag(L"Goal");
	}

	void Goal::OnUpdate()
	{
		//両方のプレイヤーに触れたら
		if (isCollPlayer && isCollPlayer2)
		{
			PlayerGoal();
		}
	}

	void Goal::PlayerGoal()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];

		//スプライトの表示
		if (!isDisplaySprite)
		{
			GetStage()->AddGameObject<Sprites>()->CreateSprite(Vec3(-400.0f, 250.0f, 0.0f), Vec2(800, 130), L"CLEAR");
			GetStage()->AddGameObject<ButtonSprite>(Vec3(-400.0f, -50.0f, 0.0f), L"BACKTOTITLE");
			isDisplaySprite = true;
		}

		//カメラのゴール後にズーム演出
		//auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		//ptrCamera->ZoomCamera();
		
		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->ZoomCamera();

		//Ｂボタンを押したらタイトルへ
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B || pad2.wPressedButtons & XINPUT_GAMEPAD_B) {
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
		}
	}

	void Goal::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayer && m_Position.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x) {
			isCollPlayer = true;
		}
		if (ptrPlayer2 && m_Position.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x) {
			isCollPlayer2 = true;
		}
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
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.7f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"RingObject_MESH");
		drawComp->SetTextureResource(L"SAVEPOINT_TX");
		drawComp->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale.x + 2, m_Scale.y + 7.5, m_Scale.z / (float)3);
		transComp->SetRotation(0.0f, XM_PIDIV2, 0.0f);

		SetAlphaActive(true);

		AddTag(L"SavePoint");
	}

	void SavePoint::OnUpdate()
	{
		//両方のプレイヤーに触れたら
		if (isCollPlayer && isCollPlayer2)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"PURPLE_TX");
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
	}

	void SavePoint::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);
		auto ptrPos = GetComponent<Transform>()->GetPosition();

		if (ptrPlayer && ptrPos.x < ptrPlayer->GetComponent<Transform>()->GetPosition().x && !isCollPlayer) {
			isCollPlayer = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"RED_TX");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
		}
		if (ptrPlayer2 && ptrPos.x < ptrPlayer2->GetComponent<Transform>()->GetPosition().x && !isCollPlayer2) {
			isCollPlayer2 = true;
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"BLUE_TX");
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
		}
	}

	//ゴールの上の四角赤仮設置
	GoalSquareRed::GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	GoalSquareRed::~GoalSquareRed() {}

	void GoalSquareRed::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNRED_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		AddTag(L"GoalSquareRed");
	}

	void GoalSquareRed::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//ゴールの上の四角青仮設置
	GoalSquareBlue::GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	GoalSquareBlue::~GoalSquareBlue() {}

	void GoalSquareBlue::OnCreate()
	{
		// 頂点データ
		m_vertices = {
			//  Position,			   Texture(UV座標)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // 左上:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // 右上:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // 左下:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // 右下:3
		};

		// 頂点インデックス
		m_indices = {
			0, 1, 2,  
			2, 1, 3,  
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true); 
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"TENNSENNBLUE_TX");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		AddTag(L"GoalSquareBlue");
	}

	void GoalSquareBlue::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}
}
