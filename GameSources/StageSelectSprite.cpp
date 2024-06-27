/*!
*
@file StageSelect.cpp
ステージセレクトシーンに使うスプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------	//--------------------------------------------------------------------------------------
	SelectSprite::SelectSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_textureKey(TextureKey),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos)
	{}

	SelectSprite::~SelectSprite() {}
	void SelectSprite::OnCreate() {
		Col4 m_color = Col4(1.0f);
		float helfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), m_color, Vec2(1.0f, 1.0f)) },
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos);
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);

		SetDrawLayer((int)DrawLayer::ForeFront);

	}

	void SelectSprite::OnUpdate() {
	}

	//選択されているスプライトの点滅処理
	void SelectSprite::Flashing() {
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		//透明度の変更処理
		if (m_alpha <= 0.0f) {
			n = +1.0f;
		}
		if (m_alpha >= 1.0f) {
			n = -1.0f;
		}
		m_alpha += sin(n) * delta;
		ptrDraw->SetDiffuse(Col4(1.0, 1.0f, 1.0f, m_alpha));
	}

	//ステージセレクトに使用する黄色カーソルのスプライト
	CursorSprite::CursorSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_textureKey(TextureKey),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos)
	{}

	CursorSprite::~CursorSprite() {}
	void CursorSprite::OnCreate() {
		Col4 m_color = Col4(1.0f);
		float helfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), m_color, Vec2(1.0f, 1.0f)) },
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos);
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
		SetDrawLayer((int)DrawLayer::ForeFront);
		
	}

	void CursorSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 5.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0, 1.0, 1.0, 1.0);
		col.w = sin(m_TotalTime) * 0.5f + 0.5f;
		PtrDraw->SetDiffuse(col);
	}

	//透明度の変更処理
	void CursorSprite::Flashing() {
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		if (m_alpha <= 0.0f) {
			n = +1.0f;
		}
		if (m_alpha >= 1.0f) {
			n = -1.0f;
		}
		m_alpha += sin(n) * delta;
		ptrDraw->SetDiffuse(Col4(1.0, 1.0f, 1.0f, m_alpha));
	}
}