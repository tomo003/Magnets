/*!
@file GameObjectSample.cpp
@brief CSV�t�@�C���ǂݍ��݊m�F�p���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�X�e�[�W�̒ʏ�u���b�N�̉��ݒu
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

	void Block::OnUpdate() {
	}

	//�e�N�X�`�����ύX�ł���l�p���I�u�W�F�N�g
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
