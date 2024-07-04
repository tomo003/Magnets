/* !
@file BackGroundSprite.h
@brief 背景の実装
@author 佐藤悠
@detail　タイトルやゲームステージでの背景を実装
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//画像ループの背景
	//--------------------------------------------------------------------------------------
	/*
	* @param tex	使用テクスチャ
	*/
	class BackGroundSprite : public GameObject {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // 初期サイズ
		wstring m_tex; //使用テクスチャ
	public:
		// コンストラクタ
		BackGroundSprite(const shared_ptr<Stage>& stage,const wstring tex) :
			GameObject(stage),
			m_tex(tex),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; 
	};

	//--------------------------------------------------------------------------------------
	//画像ごとの背景
	//--------------------------------------------------------------------------------------
	/*
	* @param scale		表示サイズ
	* @param position	表示位置
	* @param texKey		使用テクスチャ
	*/
	class BackGroundSprite2 : public GameObject {
		
		Vec3 m_scale;	 //表示サイズ
		Vec3 m_position; //表示位置
		wstring m_texkey;//使用テクスチャ

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