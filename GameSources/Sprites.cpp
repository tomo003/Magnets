/*!
@file Sprites.cpp
@brief 画像処理の基本クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_spriteSize(Vec2(0.0f)),
		m_afterSize(Vec2(0.0f)),
		m_position(Vec3(0.0f)),
		m_uiSizeCoefficient(0.0f),
		m_totalTime(0.0f),
		m_waitSecond(5.0f),
		m_alphaNum(0.0f),
		m_fadeSpeed(0.01f),
		m_spriteType(SpriteType::Normal),
		m_fadeType(FadeType::None),
		m_isSeekSizeState(SeekSizeState::Wait),
		m_seekType(SeekType::BottomRight),
		m_isChangeColorState(ChangeColorState::DefaultSpeed)
	{
	}
	// デストラクタ
	Sprites::~Sprites() {}

	void Sprites::CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey)
	{
		// 表示位置と表示サイズをメンバ変数に入れておく
		m_position = position;
		m_spriteSize = size;

		// 頂点データの設定 //
		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);
		m_vertices = {
			{Vec3(0.0f	 , 0.0f	   , 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(size.x , 0.0f	   , 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(0.0f	 , -size.y , 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(size.x , -size.y , 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};
		m_indices = {
			0, 1, 2,
			2, 1, 3
		};
		// ここまで //

		// 見た目の設定
		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(texKey);

		// 位置の設定
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// 透過処理を有効にする
		SetAlphaActive(true);
		// 描画レイヤーを最前面に
		SetDrawLayer((int)DrawLayer::ForeFront);
	}

	void Sprites::CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType) {

		// フェードアウトかフェードインか取得
		m_fadeType = fadeType;

		// フェードインなら
		if (m_fadeType == FadeType::FadeIn) {
			// アルファ値を1に
			m_alphaNum = 1.0f;
		}
		else if (m_fadeType == FadeType::FadeOut) // フェードアウトなら
		{
			// アルファ値を0に
			m_alphaNum = 0.0f;
		}

		// スプライトの作成
		CreateSprite(position, size, texKey);
	}

	void Sprites::UpdateFlashingSprite(int flashSpeed)
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime(); // 時間の取得

		// サインカーブを使って点滅を表現
		float color = sinf(m_totalTime);
		// 値を常に+値にする処理
		if (color < 0.0f)
		{
			color *= -1;
		}

		// 変化速度を反映(一定速度)
		m_totalTime += delta * flashSpeed;

		// 頂点データの更新
		auto drawComp = GetComponent<PCTSpriteDraw>();
		m_vertices[0].color = Col4(color, color, color, 1.0f);
		m_vertices[1].color = Col4(color, color, color, 1.0f);
		m_vertices[2].color = Col4(color, color, color, 1.0f);
		m_vertices[3].color = Col4(color, color, color, 1.0f);
		drawComp->UpdateVertices(m_vertices);
	}

	void Sprites::UpdateFlashingSprite(int flashSpeed, int afterFlashSpeed, bool speedChangeTrigger)
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得

		// サインカーブを使って点滅を表現
		float color = sinf(m_totalTime);
		// 値を常に+値にする処理
		if (color < 0.0f)
		{
			color *= -1;
		}

		// 通常の速度なら
		if (m_isChangeColorState == ChangeColorState::DefaultSpeed)
		{
			m_totalTime += delta * flashSpeed; // 変化速度を反映

			// 頂点データの更新
			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(color, color, color, 1.0f);
			m_vertices[1].color = Col4(color, color, color, 1.0f);
			m_vertices[2].color = Col4(color, color, color, 1.0f);
			m_vertices[3].color = Col4(color, color, color, 1.0f);
			drawComp->UpdateVertices(m_vertices);

			// トリガーがtrueになったら
			if (speedChangeTrigger)
			{
				// スピードを変化させる
				m_isChangeColorState = ChangeColorState::SpeedChange;
			}
		}

		// ステートがスピード変化状態なら
		if (m_isChangeColorState == ChangeColorState::SpeedChange)
		{
			m_totalTime += delta * afterFlashSpeed; // 変化速度を反映

			// 頂点データの更新
			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(color, color, color, 1.0f);
			m_vertices[1].color = Col4(color, color, color, 1.0f);
			m_vertices[2].color = Col4(color, color, color, 1.0f);
			m_vertices[3].color = Col4(color, color, color, 1.0f);
			drawComp->UpdateVertices(m_vertices);

			// トリガーがfalseになったら
			if (!speedChangeTrigger)
			{
				// スピードを戻す
				m_isChangeColorState = ChangeColorState::DefaultSpeed;
			}
		}
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType)
	{
		// ステートが停止状態でなければ
		if (m_isSeekSizeState != SeekSizeState::Stop)
		{
			// サイズ変更状態になる
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}

		// サイズ変更状態なら
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			// 時間の取得
			auto& app = App::GetApp();
			auto delta = app->GetElapsedTime();

			// サイズ係数を変化させる
			m_uiSizeCoefficient += delta / seekSecond;

			// どの頂点を基準にするか
			switch (seekType)
			{
			case SeekType::UpperLeft: // 左上
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::UpperRight: // 右上
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite: // 
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft: // 左下
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight: // 右下
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				break;

			default: // 例外なら何もしない
				break;
			}

			// 頂点データの更新
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(m_vertices);

			// 係数が1より大きくなったら
			if (m_uiSizeCoefficient > 1.0f)
			{
				// 係数を1に固定する
				m_uiSizeCoefficient = 1.0f;
			}

		}
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType, float waitSecond)
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		// 待機時間用
		m_totalTime += delta;

		// 待機時間が終わっているかつステートが停止状態でなければ
		if (m_totalTime > waitSecond && m_isSeekSizeState != SeekSizeState::Stop)
		{
			// サイズ変更状態に移行
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}

		// サイズ変更状態なら
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			// 係数を変化
			m_uiSizeCoefficient += delta / seekSecond;

			// どの頂点を基準にするか
			switch (seekType)
			{
			case SeekType::UpperLeft: // 左上
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft: // 左下
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight: // 右下
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				break;

			default:
				break;
			}

			// 頂点データの更新
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(m_vertices);

			// 係数が1以上になったら
			if (m_uiSizeCoefficient > 1.0f)
			{
				// 停止状態になる
				m_isSeekSizeState = SeekSizeState::Stop;
			}
		}
	}

	void Sprites::UpdateFadeSprite(float fadeSecond)
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		// フェードタイプがフェードインなら
		if (m_fadeType == FadeType::FadeIn)
		{
			// アルファ値を減少させる
			m_alphaNum -= delta / fadeSecond;

			// アルファ値の反映
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
		}

		// フェードタイプがフェードアウトなら
		if (m_fadeType == FadeType::FadeOut)
		{
			// アルファ値を減少させる
			m_alphaNum += delta / fadeSecond;

			// アルファ値の反映
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
		}
	}
}