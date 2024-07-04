/*!
@file GameObjectSample.h
@brief ゲームステージのオブジェクト
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//地面オブジェクト
	//--------------------------------------------------------------------------------------
	class Block : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		//構築と破棄
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
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//テクスチャ変更が可能な四角いオブジェクト
	//--------------------------------------------------------------------------------------
	class ChangeTextureBlock : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		//構築と破棄
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
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//スタートオブジェクト
	//--------------------------------------------------------------------------------------
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//構築と破棄
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
		//初期化
		virtual void OnCreate() override;
	};
}
//end basecross
