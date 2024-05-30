/*!
@file CoinObject.h
@brief �R�C��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class CoinObject : public GameObject {
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		CoinObject(const shared_ptr<Stage>& StagePtr, const Vec3& Position) :
			GameObject(StagePtr),
			m_Position(Position)
		{
		}
		virtual ~CoinObject() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}