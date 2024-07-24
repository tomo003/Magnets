/*!
* @file BreakWall.cpp
* @brief 壊れる壁の実装
* @author 穴澤委也
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 生成
	void BreakWall::OnCreate()
	{
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(m_scale);
		m_TransComp->SetRotation(m_Rotation);
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);

		m_CollComp = AddComponent<CollisionObb>();

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.5f, 0.125f, 0.8f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTBoneModelDraw>();
		m_DrawComp->SetMeshResource(L"BreakWall_MESH");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		// アニメーションの登録
		m_DrawComp->AddAnimation(L"BREAK", 0, 15, false, 10); // 壊れる
		m_DrawComp->AddAnimation(L"BROKEN", 15, 1, true, 1); // 破壊後

		AddTag(L"BreakWall"); // 破壊可能壁のタグをつける
	}

	// 更新
	void BreakWall::OnUpdate() {
		float delta = App::GetApp()->GetElapsedTime();

		m_TransComp->SetPosition(m_position);

		// 破壊フラグがtrueのとき
		if (isBreak) {
			// アニメーションを再生する
			// UpdateAnimationはアニメーションが終了していたらtrueを返す
			if (m_DrawComp->UpdateAnimation(delta)) {
				// アニメーションが終了していたら描画と更新を止める
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

	}

	// 接触判定
	void BreakWall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		// 衝突したオブジェクトをプレイヤーにキャスト
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		// プレイヤーが反発状態かのフラグを受け取る用のフラグ(falseで初期化)
		bool PlayerRepulState = false;
		bool Player2RepulState = false;

		// 接触したオブジェクトが各プレイヤーにキャストできていたら反発状態かのフラグを受け取る
		if (ptrPlayer) PlayerRepulState = ptrPlayer->IsRepulState();
		if (ptrPlayer2) Player2RepulState = ptrPlayer2->IsRepulState();

		// プレイヤーのどちらかが反発状態で当たった時にアニメーション実行
		if (PlayerRepulState || Player2RepulState) {
			isBreak = true;
		}
	}

}
