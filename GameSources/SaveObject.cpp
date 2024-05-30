/*!
@file SaveObject.cpp
@brief �Z�[�u�I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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
		transComp->SetScale(m_Scale.x + 2, m_Scale.y + 5, m_Scale.z / (float)3);
		transComp->SetRotation(0.0f, XM_PIDIV2, 0.0f);

		SetAlphaActive(true);

		AddTag(L"SavePoint");
	}

	void SavePoint::OnUpdate()
	{
		//�����̃v���C���[�ɐG�ꂽ��
		if (isCollPlayer && isCollPlayer2)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"PURPLE_TX");
		}

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_Position);
	}

	void SavePoint::ResetTexture()
	{
		if (!isCollPlayer || !isCollPlayer2)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetTextureResource(L"SAVEPOINT_TX");
			isCollPlayer = false;
			isCollPlayer2 = false;
		}
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

	//�S�[���̏�̎l�p�ԉ��ݒu
	SaveTriangleRed::SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SaveTriangleRed::~SaveTriangleRed() {}

	void SaveTriangleRed::OnCreate()
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

	//�S�[���̏�̎l�p���ݒu
	SaveTriangleBlue::SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SaveTriangleBlue::~SaveTriangleBlue() {}

	void SaveTriangleBlue::OnCreate()
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