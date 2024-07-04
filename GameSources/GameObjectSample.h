/*!
@file GameObjectSample.h
@brief �Q�[���X�e�[�W�̃I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//�n�ʃI�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Block : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		//�\�z�Ɣj��
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
		Block::~Block() {}
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//�e�N�X�`���ύX���\�Ȏl�p���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class ChangeTextureBlock : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//�X�^�[�g�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate() override;
	};
}
//end basecross
