/*!
@file Ground.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Ground::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1.0f, 0.1f, 0.1f, 1.0f));

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);
		//transComp->SetPosition(0.0f, -1.5f, 0.0f);
		//transComp->SetScale(5.0f, 1.0f, 1.0f);


	}
}
//end basecross
