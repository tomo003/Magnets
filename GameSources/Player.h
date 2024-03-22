/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		const float ATTRACTION_CONSTANT = 100.0f; // ���͂̒萔
		const float REPEL_CONSTANT = 200.0f;   // �����̒萔
		const float MAX_SPEED = 40.0f;         // �ő呬�x

		//InputHandler<Player> m_InputHandler;

		float speed;
		Vec2 Velocity;

		float jumpCount;
		int count;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g

	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			speed(5),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();

		void MovePlayer();
		void JumpPlayer();

		void ApplyAttraction();
	};

}
//end basecross

