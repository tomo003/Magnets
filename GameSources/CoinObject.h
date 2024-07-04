/*!
@file CoinObject.h
@brief ÀÑ‚Ì’Ç‰Á
@author ²“¡—I
@detail@Œ®‚ÌÀÑ‚ğÀ‘•
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class CoinObject : public GameObject {
		Vec3 m_position;
		float m_time;
		bool palyerTouch = false;
	private:
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw;
		std::shared_ptr<CollisionObb> m_ptrColl;
	public:
		//\’z‚Æ”jŠü
		CoinObject(const shared_ptr<Stage>& StagePtr, const Vec3& position) :
			GameObject(StagePtr),
			m_position(position),
			m_time(0)
		{
		}
		virtual ~CoinObject() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& Other);

	};
}