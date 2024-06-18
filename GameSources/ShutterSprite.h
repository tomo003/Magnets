/* !
@file ShutterSprite.h
@brief タイトルシーンの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ShutterSprite : public Sprites {
		Vec2 m_DefaultSize; // 初期サイズ
		Vec3 m_Pos;
		wstring m_textureKey;
		shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
	public:
		// コンストラクタ
		ShutterSprite(const shared_ptr<Stage>& stage,Vec3& Pos,wstring );
		// デストラクタ
		~ShutterSprite();

		// 初期化
		virtual void OnCreate() override
		{
			m_ptrTrans = GetComponent<Transform>();
			Sprites::CreateSprite(m_Pos, m_DefaultSize, m_textureKey);
		}

		// 更新処理
		virtual void OnUpdate() override
		{

			Sprites::OnUpdate();
		}

		void SetPosition(const Vec3& position)
		{
			m_ptrTrans->SetPosition(position);
			m_Pos = position;
		}

		Vec3 GetPosition() const
		{
			return m_Pos;
		}
	};
}