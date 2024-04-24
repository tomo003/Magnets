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
}