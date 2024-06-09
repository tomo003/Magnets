/*!
@file StageSelect.h
@brief タイトル画面
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectScreenSprite;
	class SelectStage : public Stage {
		int m_score;

		bool stage = false;
		bool m_CntrolLock = false;
		bool m_Lock = false;
		vector<weak_ptr<SelectScreenSprite>> m_SpVec;
		shared_ptr<SoundItem> m_bgm; // サウンドアイテム

		void CreateViewLight();//ビューの作成
		void CreateSelectSprite();//スプライトの作成
		void CreateKeySprite();
		void CreateKeyLoad(const int scene ,const Vec3 pos);
		void CreateKeyRock();
		void ChangeSelect(int num);
		void CreateCursor();
		void CreateAnimeSprite();
		void PlayBGM();//BGMの作成

	public:
		SelectStage() :
			Stage(), m_SpVec(6)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

	};
}

