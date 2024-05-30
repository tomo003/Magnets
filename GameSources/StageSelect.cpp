/*!
@file StageSelect.cpp
@brief タイトル画面
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -5.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void SelectStage::CreateCursor()
	{
		auto PtrCursor = AddGameObject<CursorSprite>(
			L"CURSOR", true, Vec2(420.0f, 270.0f), Vec3(-560.0f, 180.0f, 0.0f));

		SetSharedGameObject(L"Cursor", PtrCursor);
	}
	void SelectStage::CreateSelectSprite() {
		AddGameObject<BackGroundSprite2>(Vec3(95, 60, 1.0f), Vec3(0, 0, 50), L"BACKGROUND");
		AddGameObject<SelectSprite>(L"STAGESELECT", true, Vec2(350.0f, 180.0f), Vec3(-590.0f, 390.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE1UI", true, Vec2(200.0f, 80.0f), Vec3(-560.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE2UI", true, Vec2(200.0f, 80.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE3UI", true, Vec2(200.0f, 80.0f), Vec3(520.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE4UI", true, Vec2(200.0f, 80.0f), Vec3(-560.0f, -350.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE5UI", true, Vec2(200.0f, 80.0f), Vec3(0.0f, -350.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE6UI", true, Vec2(200.0f, 80.0f), Vec3(520.0f, -350.0f, 0.0f));


	}

	void SelectStage::CreateAnimeSprite()
	{
		auto PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(-560.0f, 180.0f));
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(0.0f, 180.0f));
		m_SpVec[1] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(520.0f, 180.0f));
		m_SpVec[2] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(-560.0f, -170.0f));
		m_SpVec[3] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(0.0f, -170.0f));
		m_SpVec[4] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(520.0f, -170.0f));
		m_SpVec[5] = PtrSp;
	}
	void SelectStage::ChangeSelect(int num) {
		for (int i = 0; i < 6; i++) {
			shared_ptr<SelectScreenSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if ((i + 1) == num) {
					shptr->SetSelect(true);
				}
				else {
					shptr->SetSelect(false);
				}
			}
		}
	}



	void SelectStage::OnCreate() {
		CreateViewLight();
		CreateSelectSprite();
		CreateAnimeSprite();
		CreateCursor();
	}



	void SelectStage::OnUpdate() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];
		auto ptrCursor = GetSharedGameObject<CursorSprite>(L"Cursor");
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B || pad2.wPressedButtons & XINPUT_GAMEPAD_B) {
			if (!stage) {
				AddGameObject<FadeOut>(L"FADE_WHITE");
				PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				stage = true;
				m_Lock = true;
			}
		}

		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		if (pad.bConnected) {
			if (!m_CntrolLock && !m_Lock) {
				if (pad.fThumbLX >= 0.8f) {
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
					StageNum++;
					if (StageNum > 6) {
						StageNum = 1;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(StageNum);
					ChangeSelect(StageNum);

				}
				else if (pad.fThumbLX <= -0.8f) {
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
					StageNum--;
					if (StageNum < 1) {
						StageNum = 6;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(StageNum);
					ChangeSelect(StageNum);
				}
				else if (pad.fThumbLY >= 0.8f) {
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
					StageNum -= 3;
					if (StageNum <= 0) {
						StageNum += 6;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(StageNum);
					ChangeSelect(StageNum);
				}
				else if (pad.fThumbLY <= -0.8f) {
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
					StageNum += 3;
					if (StageNum > 6) {
						StageNum -= 6;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(StageNum);
					ChangeSelect(StageNum);
				}
			}
			else {
				if (pad.fThumbLX == 0.0f && !m_Lock) {
					m_CntrolLock = false;
				}
			}
		}
		shared_ptr<SelectScreenSprite> shptr = m_SpVec[StageNum - 1].lock();
		ptrCursor->GetComponent<Transform>()->SetPosition(shptr->GetComponent<Transform>()->GetPosition());

	}
}
//end basecross
