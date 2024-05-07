/* !
@file BackGroundSprite.h
@brief ゲームステージの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class BackGroundSprite : public GameObject {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		BackGroundSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; 
	};

	//画像ごとの背景
	/*
	* @param scale		表示サイズ
	* @param position	表示位置
	* @param texKey		使用テクスチャ
	*/
	class BackGroundSprite2 : public GameObject {
		
		Vec3 m_scale;
		Vec3 m_position;
		wstring m_texkey;

	public:
		BackGroundSprite2(const shared_ptr<Stage>& stage,
			const Vec3 scale,
			const Vec3 position,
			const wstring texkey
			) :
			GameObject(stage),
			m_scale(scale),
			m_position(position),
			m_texkey(texkey)
		{
		}

		void OnCreate() override; 
		void OnUpdate() override;
	};
}