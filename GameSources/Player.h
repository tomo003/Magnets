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
		const float LIMIT_MAX_SPEED = 5.0f;    //�v���C���[���m����Ȃ��Ă���Ƃ��̍ő呬�x

		// �v���C���[�̃W�����v�Ɏg�p����{�^��
		const WORD BUTTON_JUMP = XINPUT_GAMEPAD_A;

		//InputHandler<Player> m_InputHandler;

		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

		enum class magneticState {
			emNone = -1, // �������ĂȂ�
			emPlayer = 0, // Player
			emMagnet = 1, // MagnetN,S
			emRing = 2, // ring
			emGear = 3, // Gear
			emMetal = 4 // Metal,MoveMetal
		};

	private:
		EState m_eMagPole = EState::eN; // ���ɂ̏��
		magneticState m_emState = magneticState::emNone;

		Vec3 m_Scale = Vec3(1.0f);
		Vec3 m_pos;
		float m_speed;
		float m_speedReset;
		int m_attribute;
		Vec3 m_Velocity;
		float m_Acceleration; // �����x(���΂͋߂��قǎ��͂���������)

		Vec3 m_direction;
		float m_distance = 1000.0f;
		float m_distanceTemp;
		Vec3 m_force;

		//�v���C���[���m�������ƍs�������������鋗��
		float m_limit = 35;
		bool isRightLimit = false;
		bool isLeftLimit = false;

		Vec3 m_nearMagnetPos;//�߂����΃I�u�W�F�N�g�̈ʒu

		const Vec3 m_gravityVelocity = Vec3(0.0f, 8.0f, 0.0f);
		const Vec3 m_gravity = Vec3(0, -9.8f, 0);

		float m_playerMass = 100.0f;

		Vec3 m_objPos = Vec3(0);

		float jumpCount;
		int count;
		bool isJump = true;
		bool isInertia = false; // �x���g�R���x�A�n
		Vec3 m_inertia;

		bool isPlayerContact;

		bool isEffect = true;
		bool isGround; // ���n���Ă��邩�̔���
		bool isRepulsion = false; // �������Ă�Ƃ�true
		bool isAttration = false; // �z������Ă�Ƃ�true
		bool isBelt = false;

		bool isContactFirst = true;

		Vec3 m_RespawnPoint;//���X�|�[������ʒu

		Vec3 m_magDirUD;
		Vec3 m_magDirLR;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<BcPNTBoneModelDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<CollisionObb> m_ptrColl; // �h���[�R���|�[�l���g
		std::shared_ptr<Gravity> m_gravityComp;

		std::shared_ptr<PlayerBanner> m_playerBanner;

		bool isGearFloor = false;
		bool isStop = false;

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
			m_speedReset(5.0f),
			m_attribute(1),
			jumpCount(2),
			count(0)
		{}

		void OnCreate();
		void OnUpdate();
		void OnUpdate2();

		void MovePlayer(); // �v���C���[�̈ړ�
		void JumpPlayer(); // �v���C���[�̃W�����v(�f�o�b�O�p)
		void JumpCountReset() { // �W�����v�񐔃��Z�b�g�p
			jumpCount = 2;
		}
		void GoalPlayer();
		void SetRespawnPoint(shared_ptr<GameObject>& Other);
		void SetRespawnPoint(Vec3 RepawnPoint);
		Vec3 GetRespawnPoint()const {
			return m_RespawnPoint;
		}
		void RespawnPlayer();

		void PlayerLimit();
		void PlayerBannerPosition(Vec3 position);

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		void AnimationPlayer(eMotion Motion);

		void ApplyAttration(shared_ptr<GameObject>& Other); // �v���C���[�Ɉ��͂�K�p
		void ApplyRepulsion(shared_ptr<GameObject>& Other);  // �v���C���[�ɐ˗͂�K�p

		void PlayerApplyAttration();
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
			if (m_pos.y < magPos.y - 1.0f) {
				m_magDirUD = UP_VEC;
			}
			if (m_pos.y > magPos.y + 1.0f) {
				m_magDirUD = DOWN_VEC;
			}
			if (m_pos.x < magPos.x - 1.0f) {
				m_magDirLR = RIGHT_VEC;
			}
			if (m_pos.x > magPos.x + 1.0f) {
				m_magDirLR = LEFT_VEC;
			}
		}

		// �p�ɂ������Ȃ��悤�ɏ������ɂ��炷
		void ShiftDown(const Vec3& objPos) {
			if (m_pos.y < objPos.y - 0.9f &&
				((m_pos.x < objPos.x - 0.9f) || (m_pos.x > objPos.x + 0.9f))) {
				m_pos.y -= 0.1f;
				m_ptrTrans->SetPosition(m_pos);
			}
		}

		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void LandingJadge(shared_ptr<GameObject>& Other) {
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

		/**
		* @brief �X�s�[�h���[���ɂ���֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ZEROSpeed() {
			m_speed = 0.0f;
		}
		/**
		* @brief �X�s�[�h�����Z�b�g����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void RESETSpeed() {
			m_speed = m_speedReset;
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
		* @brief ������Ԃ�ݒ肷��֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void SetRepulState(bool state) {
			isRepulsion = state;
		}
		/**
		* @brief �z����Ԃ��ǂ����𑼃N���X�ɓn�����߂̊֐�
		* @param �����Ȃ�
		* @return bool �z����ԂȂ�true
		*/
		bool IsAttrationState() {
			return isAttration;
		}
		/**
		* @brief �z����Ԃ�ݒ肷��֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void SetAttrationState(bool state) {
			isAttration = state;
		}

		/**
		* @brief �v���C���[���S���ɌĂяo���֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		* @details ���̊֐�����RespawnPlayer���Ăяo��
		*/
		void PlayerDeath();
		void PlayerDeathEffect();


		// �S�[������
		bool IsGoal() {
			return isStop;
		}

		// GearFloor�ɐڐG���Ă��邩�ǂ�����n���֐�
		bool IsGearFloor() {
			return isGearFloor;
		}
	};

}
//end basecross

