/*!
@file GameObjectSample.cpp
@brief CSVファイル読み込み確認用仮オブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//ステージの通常ブロックの仮設置
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

	//テクスチャが変更できる四角いオブジェクト
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

		auto ptrCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//カメラにスタートオブジェクト設定
			ptrCamera->SetStartObj(GetThis<GameObject>());
		}
	}

}
