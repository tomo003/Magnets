#pragma once

#include "BaseMathInc.h"

#define RIGHT_VEC Vec3(1.0f, 0.0f, 0.0f)
#define LEFT_VEC Vec3(-1.0f, 0.0f, 0.0f)
#define UP_VEC Vec3(0.0f, 1.0f, 0.0f)
#define DOWN_VEC Vec3(0.0f, -1.0f, 0.0f)


namespace Utility
{
	/**
	 * @brief 線形補間を行う関数
	 * @param (start) 線形補間の始めの値
	 * @param (end) 線形補間の終わりの値
	 * @param (t) 線形補間の割合
	 * @return 割合に応じて補間された値
	 */
	template<class T>
	inline T Lerp(const T& start, const T& end, float t)
	{
		t = t < 0.0f ? 0.0f : t;
		t = t > 1.0f ? 1.0f : t;
		return start + (end - start) * t;
	}

	inline float RadToDeg(const float rad) {
		float deg = rad * 180.0f / XM_PI;
		return deg;
	}

	inline float DegToRad(const float deg) {
		float rad = deg * XM_PI / 180.0f;
		return rad;
	}

}