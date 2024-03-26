/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{
		const float ATTRACTION_CONSTANT = 10.0f; // ���͂̒萔
		const float REPEL_CONSTANT = 20.0f;   // �����̒萔
		const float MAX_SPEED = 4.0f;         // �ő呬�x

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
		};

	private:
		enum EState m_eMagPole = EState::eN;

		float m_speed;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		float m_playerMass = 1.0f;

		float jumpCount;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTStaticModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g

	public:
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(5),
			jumpCount(2)
		{}

		void OnCreate();
		void OnUpdate();
		//void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();

		void ApplyAttraction();
		void ApplyRepulsion();

		void limitSpeed();

		EState GetPlayerMagPole() {
			return m_eMagPole;
		}
	};

}
//end basecross

