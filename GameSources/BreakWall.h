/*!
* @file BreakWall.h
* @brief 壊れる壁
* @author 穴澤委也
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BreakWall : public GameObject
	{
	private:
		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTBoneModelDraw> m_DrawComp; // ドローコンポーネント
		std::shared_ptr<CollisionObb> m_CollComp; // コリジョンコンポーネント

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 2.5f, 0.0f);
		Vec3 m_Rotation;
		Vec3 m_scale = Vec3(1.0f, 6.0f, 1.0f);

		bool isBreak = false;
	public:
		BreakWall(
				const std::shared_ptr<Stage>& stage,
				const Vec3& position,
				const Vec3& rotation
			) :
			GameObject(stage),
			m_position(position),
			m_Rotation(rotation)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/** @brief 接触判定が起こった時に呼び出される関数
		*   @fn void OnCollisionEnter(shared_ptr<GameObject>& Other)
		*   @param Other 接触判定を起こしているオブジェクト
		*   @return 戻り値なし
		*/
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};

}