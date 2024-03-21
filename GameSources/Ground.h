/*!
@file Ground.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ground : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		Ground(const std::shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Position
			) :
			GameObject(stage),
			m_Scale(Scale),
			m_Position(Position)
		{
		}

		void OnCreate();
	};
}
//end basecross
