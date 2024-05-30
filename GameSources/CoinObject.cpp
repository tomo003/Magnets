/*!
@file CoinObject.cpp
@brief ÉRÉCÉì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CoinObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(Vec3(1.0f));
		ptrTransform->SetPosition(m_Position);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(true);
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);

		AddTag(L"CoinObject");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);
	}

	void CoinObject::OnUpdate() {

	}
}