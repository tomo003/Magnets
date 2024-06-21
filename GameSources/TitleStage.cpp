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
		//ボタンスプライトはスタンバイシーンでも使用してるっぽいので座標変えたら、スタンバイシーンのUI位置も変わる
		AddGameObject<ButtonSprite>(Vec3( - 400.0f, 50.0f, 0.0f), L"BPUSH");

	} 

	//void TitleStage::PlayBGM() {
	//	m_bgm = App::GetApp()->GetXAudio2Manager()->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.0f);
	//}


	void TitleStage::OnCreate() {
		CreateViewLight();
		CreateTitleSprite();
		//シャッタースプライトS（青）極の生成
		m_sFade = AddGameObject<ShutterSprite>(Vec3(780, (float)App::GetApp()->GetGameHeight() / 2, 0.0f), L"SFADE");
		//シャッタースプライトN（赤）極の生成
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

		//タイトルシーンでBボタン入力
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {

			if (!stage) {
				//スタンバイシーンに移行
				PostEvent(1.5f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				//決定音
				XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
				//シャッターが閉まる音
				XAPtr->Start(L"SHUTTER_SE", 0, 5.0f);
				//シーン移行時のシャッターテクスチャ用のフラグ
				stage = true;
			}
		}

		if (stage)
		{
			//右側に出現するS極テクスチャのX座標が-20より大きければ
			if (mRPos.x > -20.0f)
			{
				//S極テクスチャがX軸マイナスされて移動
				m_sFade->SetPosition(mRPos - Vec3(delta * 1550.0f, 0.0f, 0.0f));
			}
			//一定まで行ったら移動が止まる
			else
			{
				m_sFade->SetPosition(Vec3(-20.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
			//右側に出現するS極テクスチャのX座標が-810より小さかったら
			if (mLPos.x < -810.0f)
			{
				//N極テクスチャがX軸プラスされて移動
				m_nFade->SetPosition(mLPos - Vec3(-delta * 1550.0f, 0.0f, 0.0f));
			}
			//一定まで行ったら移動が止まる
			else
			{
				m_nFade->SetPosition(Vec3(-810.0f, (float)App::GetApp()->GetGameHeight() / 2, 0.0f));
			}
		}
	}
}
//end basecross
