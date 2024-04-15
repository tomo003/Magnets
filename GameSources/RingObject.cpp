#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void RingObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CYLINDER");
		m_ptrDraw->SetTextureResource(L"GRAY_TX");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(m_position);
		m_ptrTrans->SetScale(Vec3(2.0f));
		m_ptrTrans->SetRotation(XM_PIDIV2, 0.0f, 0.0f);

		SetAlphaActive(true);

		//auto ptrArea = GetStage()->AddGameObject<MagnetArea>(m_position, m_MagAreaRadius, L"TYPEALL_TX");

	}

	void RingObject::OnUpdate() {

	}
}