/* !
@file ButtonUI.h
@brief ボタンの実装
@author 佐藤悠
@detail　UIで使うボタンの実装
*/

#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ButtonSprite : public Sprites {
		const Vec2 m_DefaultSize;//初期サイズ

		bool m_changeSpeed; //ボタンが押されたら点滅速度変更フラグ

		Vec3 m_pos;
		wstring m_texkey;

	public:
		//コンストラクタ
		ButtonSprite(const shared_ptr<Stage>& stage , const Vec3& pos,const wstring& texkey);
		//デストラクタ
		~ButtonSprite();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

	};

	class UiSprite : public Sprites {
		Vec2 m_size;
		Vec3 m_pos;
		wstring m_texkey;
		int m_layer;
	public:
		//コンストラクタ
		UiSprite(const shared_ptr<Stage>& stage , const Vec2& size, const Vec3& pos,const wstring& texkey,const int& layer);
		//デストラクタ
		~UiSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}