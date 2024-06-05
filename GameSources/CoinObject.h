/*!
@file CoinObject.h
@brief �R�C��
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
	public:
		//�\�z�Ɣj��
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