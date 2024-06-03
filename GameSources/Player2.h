/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player2 : public GameObject
	{
		const float ATTRACTION_CONSTANT = 150.0f; // ���͂̒萔
		const float REPEL_CONSTANT = 400.0f;   // �����̒萔
		const float MAX_SPEED = 20.0f;         // �ő呬�x
		const float LIMIT_MAX_SPEED = 5.0f;    //�v���C���[���m����Ȃ��Ă���Ƃ��̍ő呬�x

		// �v���C���[�̃W�����v�Ɏg�p����{�^��
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
		};

	private:
		enum EState m_eMagPole = EState::eS; // ���ɂ̏��

		Vec3 m_pos;
		float m_speed;
		int m_attribute;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		Vec3 m_direction;
		float m_distance = 1000.0f;
		float m_distanceTemp;
		Vec3 m_force;

		//�v���C���[���m�������ƍs�������������鋗��
		float m_limit = 20;
		bool isLimit = false;

		Vec3 m_nearMagnetPos;//�߂����΃I�u�W�F�N�g�̈ʒu

		const Vec3 m_gravityVelocity = Vec3(0.0f, 8.0f, 0.0f);
		const Vec3 m_gravity = Vec3(0, -9.8f, 0);

		float m_playerMass = 100.0f;

		Vec3 m_objPos = Vec3(0);

		float jumpCount;
		int count;
		bool isJump = true;
		bool isGround;
		bool isInertia = false;
		Vec3 m_inertia;

		bool isPlayerContact;
		bool isRepulsion = false; // �������Ă�Ƃ�true
		bool isEffect = true;

		float m_RespawnPoint;//���X�|�[������ʒu

		wstring m_magDirLR;
		wstring m_magDirUD;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<Gravity> m_gravityComp;

		std::shared_ptr<PlayerBanner> m_playerBanner;

		bool isGoal = false;

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
			m_speed(5.0f),
			m_attribute(1),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		void OnUpdate2();

		void MovePlayer();
		void JumpPlayer();
		void JumpCountReset() {
			jumpCount = 2;
		}
		void SetRespawnPoint(shared_ptr<GameObject>& Other);
		void SetRespawnPoint(float RepawnPoint);
		float GetRespawnPoint()const {
			return m_RespawnPoint;
		}
		void RespawnPlayer();

		void PlayerLimit();

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void AnimationPlayer(eMotion Motion);

		void ApplyAttraction(shared_ptr<GameObject>& Other); // �v���C���[�Ɉ��͂�K�p
		void ApplyRepulsion(shared_ptr<GameObject>& Other);  // �v���C���[�ɐ˗͂�K�p

		void PlayerApplyAttraction();
		void PlayerApplyRepulsion();

		void ApplyForcePlayer();

		void limitSpeed();
		void PlayerBannerPosition(Vec3 position);

		// �v���C���[�̎��ɂ𑼃N���X�Ŏ擾����p�̊֐�
		EState GetPlayerMagPole() {
			return m_eMagPole;
		}
		void SetPlayerMagPole(int i);

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
		pair<wstring, wstring> GetMsgnetsDirection() {
			return make_pair(m_magDirLR, m_magDirUD);
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		/**
		* @brief ������Ԃ��ǂ����𑼃N���X�ɓn�����߂̊֐�
		* @param �����Ȃ�
		* @return bool ������ԂȂ�true
		*/
		bool IsRepulState() {
			return isRepulsion;
		}

		/**
		* @brief �v���C���[���S���ɌĂяo���֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		* @details ���̊֐�����RespawnPlayer���Ăяo��
		*/
		void PlayerDeath();

		// �S�[������
		bool IsGoal() {
			return isGoal;
		}
	};

}
//end basecross
