/*!
@file MovieStage.cpp
@brief タイトルムービーを流す
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージ
	//--------------------------------------------------------------------------------------
	void TitleMovieStage::CreateViewLight() {
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

	// 生成
	void TitleMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//メディアディレクトリを取得
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"Movie\\";
		wstring strMovie = dataDir + L"MagnetsMOVIE.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();

		// フェードアウト用のスプライトを用意
		m_ptrSprite = AddGameObject<Sprites>();
		Vec2 Size = Vec2(App::GetApp()->GetGameWidth(), App::GetApp()->GetGameHeight());
		m_ptrSprite->CreateSprite(Vec3(-Size.x / 2, Size.y / 2, 0.0f), Size, L"FADE_BLACK");
		m_ptrSpriteDraw = m_ptrSprite->GetComponent<PCTSpriteDraw>();
		m_ptrSpriteDraw->SetDiffuse(m_diffuseColor);
	}

	// 更新
	void TitleMovieStage::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleMovieStage>());

		if (isFadeOut)
		{
			m_diffuseColor.w += delta / m_FadeTime; // 透明度をフェードにかける時間(1秒)で1.0になるように加算
			m_ptrSpriteDraw->SetDiffuse(m_diffuseColor); // 色をセット
			if (m_diffuseColor.w >= 1.0f) // 透明度が1.0以上になったら
			{
				// タイトルステージに遷移
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}
	}

	//ボタン(どこでも)
	void TitleMovieStage::OnPushAny() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//決定音
		XAPtr->Start(L"BUTTON_SE", 0, 2.0f);
		// フェードアウトフラグをtrue
		isFadeOut = true;
	}
}