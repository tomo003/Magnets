/*!
* @file HammerObject.h
* @brief �n���}�[�I�u�W�F�N�g
* @author ���V�ϖ�
* @details	�n���}�[�I�u�W�F�N�g
*			�n���}�[�̑O���G���A�̔���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class HammerObject : public GameObject
	{
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3
		};

	};
}