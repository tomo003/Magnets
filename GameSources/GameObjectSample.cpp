/*!
@file GameObjectSample.cpp
@brief ゲームステージのオブジェクト
@autor 吉田鈴
@detail ステージ上にCSVで作成されるオブジェクト実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// 地面オブジェクト
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
	// テクスチャ変更が可能な四角いオブジェクト
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
	// スタートオブジェクト
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
			// カメラにスタートオブジェクト設定
			ptrCamera->SetStartObj(GetThis<GameObject>());
		}
	}

}
