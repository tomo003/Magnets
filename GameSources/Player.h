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
		const float REPEL_CONSTANT = 100.0f;   // �����̒萔
		const float MAX_SPEED = 10.0f;         // �ő呬�x

		// �v���C���[�̃W�����v�Ɏg�p����{�^��
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
		};

	private:
		enum EState m_eMagPole = EState::eFalse; // ���ɂ̏��

		Vec3 m_pos;
		float m_speed;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		Vec3 m_gravityTemp;

		float m_playerMass = 1.0f;

		float jumpCount;
		int count;

		wstring m_magDirLR;
		wstring m_magDirUD;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<Gravity> m_gravityComp;

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
		Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(5),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		//void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void AnimationPlayer(eMotion Motion);

		void ApplyAttraction(); // �v���C���[�Ɉ��͂�K�p
		void ApplyRepulsion();  // �v���C���[�ɐ˗͂�K�p

		void limitSpeed(); // ���x������������

		// �v���C���[�̎��ɂ𑼃N���X�Ŏ擾����p�̊֐�
		EState GetPlayerMagPole() {
			return m_eMagPole;
		}

		// �߂����΂��������猩��4�����̂ǂ��ɂ��邩�ݒ�
		void SetMsgnetsDirection(const Vec3& magPos) {
			if (m_pos.y < magPos.y) {
				m_magDirUD = L"UP";
			}
			if (m_pos.y > magPos.y) {
				m_magDirUD = L"DOWN";
			}
			if (m_pos.x < magPos.x) {
				m_magDirLR = L"RIGHT";
			}
			if (m_pos.x > magPos.x) {
				m_magDirLR = L"LEFT";
			}
		}
		// ���̂��擾
		pair<wstring,wstring> GetMsgnetsDirection() {
			return make_pair(m_magDirLR, m_magDirUD);
		}
	};

}
//end basecross

