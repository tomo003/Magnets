/*!
@file StageSelect.cpp
@brief ステージセレクトシーン
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
	//曲
	void SelectStage::PlayBGM() {
		m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"STANDBY_BGM", XAUDIO2_LOOP_INFINITE, 3.0f);
	}

	void SelectStage::CreateCursor()
	{
		//黄色カーソルの生成処理　Vec2（サイズ）、Vec3（生成座標）
		auto PtrCursor = AddGameObject<CursorSprite>(
			L"CURSOR", true, Vec2(420.0f, 270.0f), Vec3(-560.0f, 180.0f, 0.0f));

		SetSharedGameObject(L"Cursor", PtrCursor);
	}
	//ステージセレクトシーンに生成されるカーソル以外のスプライト
	void SelectStage::CreateSelectSprite() {

		//背景
		AddGameObject<BackGroundSprite2>(Vec3(95, 60, 1.0f), Vec3(0, 0, 50), L"BACKGROUND1");

		//左上のステージセレクトの文字
		AddGameObject<SelectSprite>(L"STAGESELECT", true, Vec2(370.0f, 150.0f), Vec3(-590.0f, 390.0f, 0.0f));

		//ステージ内の画面のスクショスプライト
		AddGameObject<SelectSprite>(L"STAGE1UI", true, Vec2(230.0f, 70.0f), Vec3(-650.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE2UI", true, Vec2(230.0f, 70.0f), Vec3(-100.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE3UI", true, Vec2(230.0f, 70.0f), Vec3(420.0f, 0.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE4UI", true, Vec2(230.0f, 70.0f), Vec3(-650.0f, -350.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE5UI", true, Vec2(230.0f, 70.0f), Vec3(-100.0f, -350.0f, 0.0f));
		AddGameObject<SelectSprite>(L"STAGE6UI", true, Vec2(230.0f, 70.0f), Vec3(420.0f, -350.0f, 0.0f));


	}

	void SelectStage::CreateKeyLoad(const int scene, const Vec3 pos) {
		int score = App::GetApp()->GetScene<Scene>()->GetScore(scene);
		switch (score) {
		case 0:
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 1:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		case 2:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"NOKEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		default:
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 50.0f, pos.y, 0.0f));
			AddGameObject<SelectSprite>(L"KEY", true, Vec2(100.0f, 100.0f), Vec3(pos.x + 100.0f, pos.y, 0.0f));
			break;
		}
	}
	void SelectStage::CreateKeySprite() {
		auto scene = App::GetApp()->GetScene<Scene>();
		int StageNum = scene->GetStageNum();
		for (int i = 0; i < 7; i++) {
			switch (i) {
			case 1:
				CreateKeyLoad(1, Vec3(-500.0f, 0.0f, 0.0f));
				break;
			case 2:
				CreateKeyLoad(2, Vec3(50.0f, 0.0f, 0.0f));
				break;
			case 3:
				CreateKeyLoad(3, Vec3(580.0f, 0.0f, 0.0f));
				break;
			case 4:
				CreateKeyLoad(4, Vec3(-500.0f, -350.0f, 0.0f));
				break;
			case 5:
				CreateKeyLoad(5, Vec3(50.0f, -350.0f, 0.0f));
				break;
			case 6:
				CreateKeyLoad(6, Vec3(580.0f, -350.0f, 0.0f));
				break;
			default:
				break;
			}
		}
	}

	void SelectStage::CreateKeyRock() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		m_score = 15;
		for (int i = 1; i < 7; i++) {
			m_score += PtrScene->GetScore(i);
		}

		if (m_score < 7) {
			AddGameObject<UiSprite>(Vec2(400.0f, 250.0f), Vec3(-760.0f, -50.0f, 0.0f), L"ROCK" ,2);
			AddGameObject<UiSprite>(Vec2(140.0f, 140.0f), Vec3(-690.0f, -70.0f, 0.0f), L"KEY", 2);
			AddGameObject<UiSprite>(Vec2(160.0f, 60.0f), Vec3(-600.0f, -140.0f, 0.0f), L"KEY7", 2);
		}
		if (m_score < 10) {
			AddGameObject<UiSprite>(Vec2(400.0f, 250.0f), Vec3(-200.0f, -50.0f, 0.0f), L"ROCK" ,2);
			AddGameObject<UiSprite>(Vec2(140.0f, 140.0f), Vec3(-130.0f, -70.0f, 0.0f), L"KEY", 2);
			AddGameObject<UiSprite>(Vec2(160.0f, 60.0f), Vec3(-40.0f, -140.0f, 0.0f), L"KEY10", 2);
		}
		if (m_score < 13) {
			AddGameObject<UiSprite>(Vec2(400.0f, 250.0f), Vec3(320.0f, -50.0f, 0.0f), L"ROCK" ,2);
			AddGameObject<UiSprite>(Vec2(140.0f, 140.0f), Vec3(390.0f, -70.0f, 0.0f), L"KEY", 2);
			AddGameObject<UiSprite>(Vec2(160.0f, 60.0f), Vec3(480.0f, -140.0f, 0.0f), L"KEY13", 2);
		}

	}

	void SelectStage::CreateAnimeSprite()
	{
		auto PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE1", true, Vec2(400.0f, 250.0f), Vec2(-560.0f, 180.0f));
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE2", true, Vec2(400.0f, 250.0f), Vec2(0.0f, 180.0f));
		m_SpVec[1] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE3", true, Vec2(400.0f, 250.0f), Vec2(520.0f, 180.0f));
		m_SpVec[2] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE4", true, Vec2(400.0f, 250.0f), Vec2(-560.0f, -170.0f));
		m_SpVec[3] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE5", true, Vec2(400.0f, 250.0f), Vec2(0.0f, -170.0f));
		m_SpVec[4] = PtrSp;
		PtrSp = AddGameObject<SelectScreenSprite>(L"STAGE6", true, Vec2(400.0f, 250.0f), Vec2(520.0f, -170.0f));
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
		CreateKeyRock();
		CreateCursor();
		CreateKeySprite();
		PlayBGM();
	}

	void SelectStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}


	void SelectStage::OnUpdate() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];
		auto ptrCursor = GetSharedGameObject<CursorSprite>(L"Cursor");


		if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int StageNum = PtrScene->GetStageNum();
			//m_score = 0;
			//for (int i = 1; i < 7; i++) {
			//	m_score += PtrScene->GetScore(i);
			//}

			if (StageNum <= 3) {
				if (!stage) {
					AddGameObject<FadeOut>(L"FADE_WHITE");
					PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
					stage = true;
					m_Lock = true;
				}
			}
			else if (StageNum == 4) {
				if (!stage) {
					if (m_score >= 7) {
						AddGameObject<FadeOut>(L"FADE_WHITE");
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
						stage = true;
						m_Lock = true;
					}
				}
			}
			else if (StageNum == 5) {
				if (m_score >= 10) {
					if (!stage) {
						AddGameObject<FadeOut>(L"FADE_WHITE");
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
						stage = true;
						m_Lock = true;
					}
				}
			}
			else if (StageNum == 6) {
				if (m_score >= 13) {
					if (!stage) {
						AddGameObject<FadeOut>(L"FADE_WHITE");
						PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						auto XAPtr = App::GetApp()->GetXAudio2Manager();
						XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
						stage = true;
						m_Lock = true;
					}
				}
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
