/*!
@file CoinObject.h
@brief ÉRÉCÉì
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class CoinObject : public GameObject {
		Vec3 m_Position;
	public:
		//ç\ízÇ∆îjä¸
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