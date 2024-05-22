/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject
	{

		//const float ATTRACTION_CONSTANT = 150.0f; // ���͂̒萔
		//const float REPEL_CONSTANT = 200.0f;   // �����̒萔
		//const float MAX_SPEED = 10.0f;         // �ő呬�x
		const float ATTRACTION_CONSTANT = 150.0f; // ���͂̒萔
		const float REPEL_CONSTANT = 400.0f;   // �����̒萔
		const float MAX_SPEED = 20.0f;         // �ő呬�x

		// �v���C���[�̃W�����v�Ɏg�p����{�^��
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
		};

	private:
		enum EState m_eMagPole = EState::eN; // ���ɂ̏��

		Vec3 m_pos;
		float m_speed;
		int m_attribute;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		Vec3 m_direction;
		float m_distance = 1000.0f;
		float m_distanceTemp;
		Vec3 m_force;

		Vec3 m_nearMagnetPos;//�߂����΃I�u�W�F�N�g�̈ʒu

		const Vec3 m_gravityVelocity = Vec3(0.0f, 8.0f, 0.0f);
		const Vec3 m_gravity = Vec3(0, -9.8f, 0);

		float m_playerMass = 100.0f;

		float jumpCount;
		int count;
		bool isJump = true;
		bool isInertia = false;
		Vec3 m_inertia;

		bool isPlayerContact;

		bool isEffect = true;
		bool isGround; // ���n���Ă��邩�̔���
		bool isCollGear; // ���ԂƂ������Ă��邩�̔���

		float m_RespawnPoint;//���X�|�[������ʒu

		wstring m_magDirLR;
		wstring m_magDirUD;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<Gravity> m_gravityComp;

		bool isCollRing = false; // �����O�ƐڐG���Ă��邩(�����l��false)
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
		Player(const std::shared_ptr<Stage>& stage) :
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
		void GoalPlayer();
		void SetRespawnPoint(shared_ptr<GameObject>& Other);
		float GetRespawnPoint()const {
			return m_RespawnPoint;
		}
		void RespawnPlayer(float respawnPoint);


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
		pair<wstring,wstring> GetMsgnetsDirection() {
			return make_pair(m_magDirLR, m_magDirUD);
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void LandingJadge(const shared_ptr<GameObject>& Other) {
			auto ptrOtherObjTrans = Other->GetComponent<Transform>();
			Vec3 OtherObjPos = ptrOtherObjTrans->GetPosition();
			float OtherObjScaleHalfY = ptrOtherObjTrans->GetScale().y / 2;
			float playerScaleHalfY = m_ptrTrans->GetScale().y / 2;
			float ScaleYDiff = OtherObjScaleHalfY + playerScaleHalfY;
			float PosYDiff = fabs(OtherObjPos.y - m_pos.y);

			if (PosYDiff >= ScaleYDiff) {
				isGround = true;
			}
		}

		Vec3 CycloidPos() {

		}
	};

}
//end basecross

