/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{

		shared_ptr<EfkInterface> m_EfkInterface;

	public:
		void CreateResourses();

		//テクスチャ
		void LoadTexture(const wstring& UseTextureName, const wstring& TextureDataName);
		//静的モデル
		void LoadStaticModelMesh(const wstring& staticModelMeshName, const wstring& staticModelbmfName);
		//動的モデル
		void LoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName);
		//ボーンモデル
		virtual void RegisterMultiMesh(const wstring& registerKey, const wstring& path, const wstring& fileName, bool boneUse);
		//サウンド
		void LoadSound(const wstring& soundName, const wstring& soundDataName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//エフェクトのインターフェースの取得
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}
	};

}

//end basecross
