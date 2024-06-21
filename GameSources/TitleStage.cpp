/*!
@file title.cpp
@brief タイトル画面
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
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

	void TitleStage::CreateTitleSprite() {
		AddGameObject<BackGroundSprite2>(Vec3(95, 60, 1.0f), Vec3(0, 0, 50), L"BACKGROUND1");
		
		AddGameObject<TitleSprite>();
		AddGameObject<ButtonSprite>(Vec3( - 400.0f, 50.0f, 0.0f), L"BPUSH");

	} 

	//void TitleStage::PlayBGM() {
	//	m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	//}


	void TitleStage::OnCreate() {
		CreateViewLight();
		CreateTitleSprite();
		m_sFade = AddGameObject<ShutterSprite>(Vec3(780, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"SFADE");
		m_nFade = AddGameObject<ShutterSprite>(Vec3(-1610, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"NFADE");
		//PlayBGM();
	}

	//void TitleStage::OnDestroy(){
	//	//BGMのストップ
	//	auto XAPtr = App::GetApp()->GetXAudio2Manager();
	//	XAPtr->Stop(m_bgm);
	//}


	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto& pad2 = device.GetControlerVec()[1];
		const Vec3& mLPos = m_nFade->GetPosition();
		const Vec3& mRPos = m_sFade->GetPosition();
		auto delta = App::GetApp()->GetElapsedTime();
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {

			if (!stage) {
				PostEvent(1.5f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				XAPtr->Start(L"SHUTTER_SE", 0, 5.0f);
				stage = true;
			}
		}

		if (stage)
		{
			if (mRPos.x > -20.0f)
			{
				m_sFade->SetPosition(mRPos - Vec3(delta * 1550.0f, 0.0f, 0.0f));
			}
			else
			{
				m_sFade->SetPosition(Vec3(-20.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
			if (mLPos.x < -810.0f)
			{
				m_nFade->SetPosition(mLPos - Vec3(-delta * 1550.0f, 0.0f, 0.0f));
			}
			else
			{
				m_nFade->SetPosition(Vec3(-810.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
		}
	}
}
//end basecross
