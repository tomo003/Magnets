#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BreakWall::OnCreate()
	{
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(1.0f, 6.0f, 1.0f);
		m_TransComp->SetRotation(m_Rotation);
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);

		m_CollComp = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//m_CollComp->SetDrawActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.5f, 0.125f, 0.8f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTBoneModelDraw>();
		m_DrawComp->SetMeshResource(L"BreakWall_MESH");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		m_DrawComp->AddAnimation(L"BREAK", 0, 15, false, 10);
		m_DrawComp->AddAnimation(L"BROKEN", 15, 1, true, 1);

		AddTag(L"BreakWall");
	}

	void BreakWall::OnUpdate() {
		float delta = App::GetApp()->GetElapsedTime();

		m_TransComp->SetPosition(m_position);

		if (isBreak) {
			if (m_DrawComp->UpdateAnimation(delta)) {
				SetDrawActive(false);
				SetUpdateActive(false);

			}
		}

	}

	void BreakWall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		bool PlayerRepulState = false;
		bool Player2RepulState = false;

		if (ptrPlayer) PlayerRepulState = ptrPlayer->IsRepulState();
		if (ptrPlayer2) Player2RepulState = ptrPlayer2->IsRepulState();

		if (PlayerRepulState || Player2RepulState) {
			isBreak = true;
			m_CollComp->SetUpdateActive(false);
			m_CollComp->SetDrawActive(false);
		}
	}

}
