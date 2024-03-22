#include "stdafx.h"
#include "Project.h"
#include "MagnetsObject.h"

#define COL_RED   Col4(1.0f, 0.0f, 0.0f, true)
#define COL_BLUE  Col4(0.0f, 0.0f, 1.0f, true)
#define COL_PURPLE Col4(0.56f, 0.42f, 0.78f, true)

namespace basecross {
	void MagnetsObject::OnCreate()
	{
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_ptrDraw->SetEmissive(COL_RED);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(3.5f, 0.0f, 0.0f);
		m_ptrTrans->SetScale(Vec3(0.75f));

		m_eMagPole = EState::eN;
	}

	void MagnetsObject::OnUpdate(){
		auto& app = App::GetApp();
		auto KeyState = app->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			switch(m_eMagPole) {
			case EState::eN :
				m_eMagPole = EState::eS;
				m_ptrDraw->SetEmissive(COL_BLUE);
				break;

			case EState::eS :
				m_eMagPole = EState::eN;
				m_ptrDraw->SetEmissive(COL_RED);
				break;

			case EState::eFalse :
				m_eMagPole = EState::eN;
				m_ptrDraw->SetEmissive(COL_RED);
				break;
			};
		}
		if (KeyState.m_bPressedKeyTbl['G']) {
			m_eMagPole = EState::eFalse;
			m_ptrDraw->SetEmissive(COL_PURPLE);
		}


	}

}
//end basecross

