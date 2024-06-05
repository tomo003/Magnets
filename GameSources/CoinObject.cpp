/*!
@file CoinObject.cpp
@brief ÉRÉCÉì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CoinObject::OnCreate() {
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.5f));
		ptrTrans->SetPosition(m_position);
		m_ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		m_ptrDraw->SetMeshResource(L"Key_MESH");
		m_ptrDraw->AddAnimation(L"FRY", 0, 30, true, 30);
		m_ptrDraw->AddAnimation(L"GET", 30, 30, true, 30);
		m_ptrDraw->ChangeCurrentAnimation(L"FRY");
		m_ptrColl = AddComponent<CollisionObb>();
		m_ptrColl->SetUpdateActive(true);
		//ptrColl->SetDrawActive(true);

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
		float delat = App::GetApp()->GetElapsedTime();
		m_ptrDraw->UpdateAnimation(delat * 1.0f);
		
		if (palyerTouch) {
			m_time++;
		
			if (m_time > 50.0f) {
				SetUpdateActive(false);
				SetDrawActive(false);
			}
		}
	}

	void CoinObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		if (ptrPlayer || ptrPlayer2) {
			m_ptrDraw->ChangeCurrentAnimation(L"GET");
			auto scene = App::GetApp()->GetScene<Scene>();
			int sceneNum = scene->GetStageNum();
			scene->SetScore(sceneNum);
			m_ptrColl->SetUpdateActive(false);
			palyerTouch = true;
		}
	}
}