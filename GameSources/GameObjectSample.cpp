/*!
@file GameObjectSample.cpp
@brief �Q�[���X�e�[�W�̃I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�n�ʃI�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	Block::Block(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position,
		const wstring& Texture
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Texture(Texture)
	{
	}
	Block::~Block(){}

	void Block::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_Texture);
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	//--------------------------------------------------------------------------------------
	//�e�N�X�`���ύX���\�Ȏl�p���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	ChangeTextureBlock::ChangeTextureBlock(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position,
		const wstring& Texture
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Texture(Texture)
	{
	}
	ChangeTextureBlock::~ChangeTextureBlock() {}

	void ChangeTextureBlock::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_Texture);
		drawComp->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
	}

	//--------------------------------------------------------------------------------------
	//�X�^�[�g�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
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
			//�J�����ɃX�^�[�g�I�u�W�F�N�g�ݒ�
			ptrCamera->SetStartObj(GetThis<GameObject>());
		}
	}

}
