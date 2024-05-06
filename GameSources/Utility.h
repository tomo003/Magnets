#pragma once

#include "BaseMathInc.h"

namespace Utility
{
	/**
	 * @brief ���`��Ԃ��s���֐�
	 * @param (start) ���`��Ԃ̎n�߂̒l
	 * @param (end) ���`��Ԃ̏I���̒l
	 * @param (t) ���`��Ԃ̊���
	 * @return �����ɉ����ĕ�Ԃ��ꂽ�l
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