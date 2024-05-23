/*!
@file StageSelect.h
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	class SelectSprite : public GameObject
	{
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		Col4 m_color;
		float n;
		vector<VertexPositionTexture> m_vertices;
	public:
		float m_alpha;
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		SelectSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SelectSprite();
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void Flashing();
	};

	class CursorSprite : public GameObject
	{
		float m_TotalTime;
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		Col4 m_color;
		float n;
		bool m_max;
		bool m_min;
		vector<VertexPositionTexture> m_vertices;
	public:
		float m_alpha;
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		CursorSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CursorSprite();
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void Flashing();
	};
}