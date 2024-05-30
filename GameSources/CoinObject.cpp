/*!
@file CoinObject.cpp
@brief ÉRÉCÉì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CoinObject::OnCreate() {
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.8f, 0.8f,0.1f));
		ptrTrans->SetPosition(m_position);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetDrawActive(true);

		AddTag(L"CoinObject");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.5f, 1.5f, 1.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
	}

	void CoinObject::OnUpdate() {
	}

	void CoinObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayer || ptrPlayer2) {
			SetUpdateActive(false);
			SetDrawActive(false);
		}
	}
}