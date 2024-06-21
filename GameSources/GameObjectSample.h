/*!
@file GameObjectSample.h
@brief CSVファイル読み込み確認用仮オブジェクト
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {

	//地面オブジェクト
	class Block : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		Block(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const wstring& Texture
		);
		virtual ~Block();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//テクスチャが変更できる四角いオブジェクト
	class ChangeTextureBlock : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		ChangeTextureBlock(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const wstring& Texture
		);
		virtual ~ChangeTextureBlock();
		virtual void OnCreate() override;
	};

	//スタートオブジェクト
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		Start(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Start();
		virtual void OnCreate() override;
	};
}
//end basecross
