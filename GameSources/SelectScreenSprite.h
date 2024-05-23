/*!
@file SelectScreen.h
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	class SelectScreenSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		bool m_Selected;
	public:
		//--------------------------------------------------------------------------------------		*/
		//--------------------------------------------------------------------------------------
		SelectScreenSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		virtual ~SelectScreenSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		bool IsSelect() const {
			return m_Selected;
		}
		void SetSelect(bool b) {
			m_Selected = b;
			m_TotalTime = 0.0f;
		}
	};
}
