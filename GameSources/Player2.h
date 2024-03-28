/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player2 : public GameObject
	{
		const float ATTRACTION_CONSTANT = 10.0f; // ���͂̒萔
		const float REPEL_CONSTANT = 20.0f;   // �����̒萔
		const float MAX_SPEED = 10.0f;         // �ő呬�x

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
		};

	private:
		enum EState m_eMagPole = EState::eFalse;

		float m_speed;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		float m_playerMass = 1.0f;

		float jumpCount;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		enum eMotion {
			RIGHT,
			LEFT,
			FRONT,
			BACK,
		};
		vector<wstring> m_motionKey = {
			L"RIGHT",
			L"LEFT",
			L"FRONT",
			L"BACK",
		};
		// ���݂̃t���[���̃��[�V������ێ�
		eMotion m_currentMotion;
		// �O�t���[���̃��[�V������ێ�
		eMotion m_pastMotion;


	public:
		Player2(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(5),
			jumpCount(2)
		{}

		void OnCreate();
		void OnUpdate();
		//void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();
		void DeathPlayer();

		void AnimationPlayer(eMotion Motion);

		void ApplyAttraction();
		void ApplyRepulsion();

		void PlayerApplyAttraction();
		void PlayerApplyRepulsion();

		void ApplyForcePlayer();


		void limitSpeed();

		EState GetPlayerMagPole() {
			return m_eMagPole;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

	};

}
//end basecross
