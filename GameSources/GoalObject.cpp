/*!
@file GoalObject.cpp
@brief �S�[���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g��̐Ԃ��|��
	//--------------------------------------------------------------------------------------
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
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
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

		SetDrawLayer(2);

		AddTag(L"GoalSquareRed");
	}

	void GoalSquareRed::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g��̐��|��
	//--------------------------------------------------------------------------------------
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
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�X
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

		SetDrawLayer(2);

		AddTag(L"GoalSquareBlue");
	}

	void GoalSquareBlue::ChangeTexture(wstring Texture)
	{
		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetTextureResource(Texture);
	}

	//--------------------------------------------------------------------------------------
	//�S�[���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
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

		//�S�[���I�u�W�F�N�g�̏�̔|���̒ǉ�
		m_ptrSquareRed = GetStage()->AddGameObject<GoalSquareRed>(Vec3(1.0f), Vec3(m_Position.x - 1, m_Position.y + 7, 0));
		GetStage()->SetSharedGameObject(L"GoalSquareRed", m_ptrSquareRed);
		m_ptrSquareBlue = GetStage()->AddGameObject<GoalSquareBlue>(Vec3(1.0f), Vec3(m_Position.x + 1, m_Position.y + 7, 0));
		GetStage()->SetSharedGameObject(L"GoalSquareBlue", m_ptrSquareBlue);

	}

	void Goal::OnUpdate()
	{
		//�����̃v���C���[�ɐG�ꂽ��
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

		//�X�v���C�g�̕\��
		if (!isDisplaySprite)
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"GOAL_SE", 0, 3.5f);

			GetStage()->AddGameObject<Sprites>()->CreateSprite(Vec3(-400.0f, 250.0f, 0.0f), Vec2(800, 130), L"CLEAR");
			isDisplaySprite = true;

			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene->SetGameState(GameState::GameClear);
		}

		//�J�����̃S�[����ɃY�[�����o
		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->ZoomCamera();
	}

	void Goal::GoalReset()
	{
		isCollPlayer = false;
		isCollPlayer2 = false;
	}

	void Goal::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		//�v���C���[�P���E���ɒʂ蔲������
		if (ptrPlayer && m_Position.x < ptrPlayer->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer) {
			if (!isCollPlayer2)
			{
				XAPtr->Start(L"SAVE_SE", 0, 3.5f);
			}
			isCollPlayer = true;
		}
		//�v���C���[�Q���E���ɒʂ蔲������
		if (ptrPlayer2 && m_Position.x < ptrPlayer2->GetComponent<Transform>()->GetWorldPosition().x && !isCollPlayer2) {
			if (!isCollPlayer)
			{
				XAPtr->Start(L"SAVE_SE", 0, 3.5f);
			}
			isCollPlayer2 = true;
		}
	}
}

