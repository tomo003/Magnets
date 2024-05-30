/*!
@file CoinObject.h
@brief �R�C��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class CoinObject : public GameObject {
		Vec3 m_position;
	public:
		//�\�z�Ɣj��
		CoinObject(const shared_ptr<Stage>& StagePtr, const Vec3& position) :
			GameObject(StagePtr),
			m_position(position)
		{
		}
		virtual ~CoinObject() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& Other);

	};
}