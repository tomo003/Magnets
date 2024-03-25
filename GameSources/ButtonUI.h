#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ButtonSprite : public Sprites {
		const Vec2 m_DefaultSize;//初期サイズ

		bool m_changeSpeed; //ボタンが押されたら点滅速度変更フラグ

	public:
		//コンストラクタ
		ButtonSprite(const shared_ptr<Stage>& stage);
		//デストラクタ
		~ButtonSprite();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

	};
}