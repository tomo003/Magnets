/*!
@file GameObjectSample.cpp
@brief �Q�[���X�e�[�W�̃I�u�W�F�N�g
@autor �g�c��
@detail �X�e�[�W���CSV�ō쐬�����I�u�W�F�N�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �n�ʃI�u�W�F�N�g
	//--------------------------------------------------------------------------------------
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
	// �e�N�X�`���ύX���\�Ȏl�p���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
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
	// �X�^�[�g�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	void Start::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		auto ptrCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			// �J�����ɃX�^�[�g�I�u�W�F�N�g�ݒ�
			ptrCamera->SetStartObj(GetThis<GameObject>());
		}
	}

}
