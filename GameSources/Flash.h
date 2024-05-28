﻿/*!
@file Sprites.h
@brief スプライトの親クラスの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Flash : public GameObject {
		Vec2 m_spriteSize;	// 大きさ
		Vec2 m_afterSize;	// サイズ変更後の大きさ
		Vec3 m_position;	// UIの位置

		float m_uiSizeCoefficient;	// UIサイズの係数
		float m_totalTime;			// 時間
		float m_waitSecond;			// サイズ変化までの待機時間

		float m_alphaNum;	// 透明度
		float m_fadeSpeed;	// フェードの速度

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	protected:
		enum class SpriteType {
			Normal,			// 通常
			ChangeColor,	// 色が変わる
			SeekSize,		// サイズが変わる
			Fade			// フェード処理
		};

		enum class FadeType {
			None,		// 何もしない
			FadeOut,	// フェードアウト
			FadeIn		// フェードイン
		};

		enum class SeekSizeState
		{
			Wait,		// 待機
			Stop,		// 終了
			SizeChange	// 実行
		};
		enum class SeekType {
			UpperLeft,	// 左上基準
			UpperRight,	// 右上基準
			GameSprite,	// 右上基準に動きながら縮小
			BottomLeft,	// 左下基準
			BottomRight	// 右下基準
		};

		enum class ChangeColorState {
			DefaultSpeed,	// 通常速度
			SpeedChange		// 速度変更
		};

		enum SpriteType m_spriteType = SpriteType::Normal; // スプライトタイプ
		enum FadeType m_fadeType = FadeType::None; // フェードタイプ
		enum SeekSizeState m_isSeekSizeState = SeekSizeState::Wait; // サイズ変更の状態
		enum SeekType m_seekType = SeekType::BottomRight; // 変化する方向
		enum ChangeColorState m_isChangeColorState = ChangeColorState::DefaultSpeed; // 色変更の状態

	public:
		// コンストラクタ
		Flash(const shared_ptr<Stage>& stage);

		/**
		* スプライトを作成する関数
		*
		* @param position	表示位置
		* @param size		表示サイズ
		* @param texKey		使用テクスチャ
		*
		*/
		void CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* フェードするスプライトを作成する関数
		*
		* @param position	表示位置
		* @param size		表示サイズ
		* @param texKey		使用テクスチャ
		* @param fadeType	フェードタイプ
		*/
		void CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType);

		/**
		* スプライトの点滅処理
		*
		* @param flashSpeed 点滅する速度(1でデフォルトのスピード(二秒に一回点滅))
		*/
		void UpdateFlashingSprite(const int flashSpeed);

		/**
		* スプライトの点滅処理
		*
		* @param flashSpeed 普段の速度(1でデフォルトのスピード(二秒に一回点滅))
		* @param afterFlashSpeed スピード変更後の速度
		* @param speedChangeTrigger false:通常速度 true:スピード変更後速度
		*/
		void UpdateFlashingSprite(const int flashSpeed, const int afterFlashSpeed, const bool speedChangeTrigger);

		/**
		* スプライトのサイズを変化させる処理
		*
		* @param afterSize 変化後のサイズ
		* @param seekSecond 変化にかかる時間
		* @param seekType 変化タイプ
		*/
		void UpdateSeekSizeSprite(const Vec2& afterSize, const float seekSecond, const SeekType& seekType);

		/**
		* スプライトのサイズを変化させる処理
		*
		* @param afterSize 変化後のサイズ
		* @param seekSecond 変化にかかる時間
		* @param seekType 変化タイプ
		* @param waitSecond 変化までの時間
		*/
		void UpdateSeekSizeSprite(const Vec2& afterSize, const float seekSecond, const SeekType& seekType, const float waitSecond);

		/**
		* スプライトをフェードさせる処理
		*
		* @param fadeSecond フェードにかかる時間
		*/
		void UpdateFadeSprite(const float fadeSecond);

		// サイズ変更の状態を設定する関数
		void SetSeekSizeState(const int state)
		{
			m_isSeekSizeState = (SeekSizeState)state;
		}


		void ResetColor()
		{
			float color = 1.0;
			// 頂点データの更新
			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(color, color, color, 1.0f);
			m_vertices[1].color = Col4(color, color, color, 1.0f);
			m_vertices[2].color = Col4(color, color, color, 1.0f);
			m_vertices[3].color = Col4(color, color, color, 1.0f);
			drawComp->UpdateVertices(m_vertices);
		}
	};
}
