/*!
@file GearObject.h
@brief リング型オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GearObject : public GameObject
	{

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_TransComp; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // ドローコンポーネント

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.0f);
		Vec3 m_Rotation;

		float m_RotPerSec = 30; // 一秒で30度回す

	public:
		GearObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

	class GearObjFloor : GameObject
	{
		Vec3 m_position;
		Vec3 m_Sclae = Vec3(3.0f, 0.75f, 1.0f);

	public :
		GearObjFloor(const std::shared_ptr<Stage>& stage, const Vec3& position):
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void RotToCenter(const Vec3& center, const float& rotDir);

		void ApplyForcePlayer();

		// abs関数(絶対値を求める)をVec3で使えるように
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}