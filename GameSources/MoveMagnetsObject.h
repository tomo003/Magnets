/*!
@file MoveMagnetsObject.h
@brief �ړ������΃I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveMagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3
		};

	private:
		enum EState m_eMagPole = EState::eMetal;	// ���ɂ̏��

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_ObjMass = 1.0f; // �I�u�W�F�N�g�̏d��(���͐˗͂Ŏg�p)
		float m_MagAreaRadius = 3.0f; // ���̓G���A�̔��a

		Vec3 m_position;
		float m_speed;

		std::vector<Vec3> m_points; // ����|�C���g
		int m_currentPointIndex; // ���݂̈ړ����C���ԍ�

	public:
		MoveMagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(EState::eMetal),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		// �v���C���[�Ɏ��͂ɂ��͂�K�p
		void ApplyForcePlayer();
	};

	class MoveMetalObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3
		};

	private:
		enum EState m_eMagPole = EState::eMetal;	// ���ɂ̏��

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<MagnetArea> m_ptrArea;

		float m_ObjMass = 1.0f; // �I�u�W�F�N�g�̏d��(���͐˗͂Ŏg�p)
		float m_MagAreaRadius = 3.0f; // ���̓G���A�̔��a

		Vec3 m_position;
		float m_speed;

		const std::vector<Vec3> m_points = {
			Vec3(m_position.x +3.5f, m_position.y, 0.0f), // ��
			Vec3(m_position .x -3.5f, m_position.y, 0.0f) // �E
		};

		// ����|�C���g
		int m_currentPointIndex; // ���݂̈ړ����C���ԍ�
		std::shared_ptr<EffectPlayer> m_efk;
		bool isEfkMove = true;
	public:
		MoveMetalObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(EState::eMetal),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();
		void OnDestroy()override;

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		// �v���C���[�Ɏ��͂ɂ��͂�K�p
		void ApplyForcePlayer();
		void EfkStop();
	};

	//�������p�̃{�^��
	class MoveFloorButton : public GameObject 
	{
		// �ғ���Ԃ̃X�e�[�g
		enum class EMoveState {
			eReMove, // �߂�
			eStop,   // ��~
			eMove,   // �ړ�
		};

		enum EMoveState eMoveState = EMoveState::eStop;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_actionComp; //�A�N�V�����R���|�[�l���g

		Vec3 m_position;
		Vec3 m_scale = Vec3(1.0f, 0.1f, 1.0f);

		Vec3 m_startPos; // �����ʒu
		float m_endPosY; // �ړ���̈ʒu

		float m_speed = 1.0f;


	public:
		MoveFloorButton(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void SetUp() { // �X�^�[�g�ʒu�ƒ�~�ʒu��ݒ�
			m_startPos  = m_position;
			m_endPosY = m_position.y + m_scale.y;
		}

		bool PlayerOnButton(const Vec3& hitPoint) {
			float scaleYhelf = m_scale.y / 2;
			if (hitPoint.y > m_position.y + scaleYhelf) {
				return true;
			}
			return false;
		}

		/*!
		@brief �Փ˂����u�ԂɌĂяo�����֐�
		@param �R���W�����y�A(�R���W�������)
		*/
		void OnCollisionEnter(const CollisionPair& Pair) override;
		void OnCollisionExcute(const CollisionPair& Pair) override;
		void OnCollisionExit(const CollisionPair& Pair) override;
	};

	// �{�^���œ�����
	class MoveFloor : public GameObject
	{
		// �ғ���Ԃ̃X�e�[�g
		enum class EMoveState {
			eReMove, // �߂�
			eStop,   // ��~
			eMove,   // �ړ�
		};

		enum EMoveState eMoveState = EMoveState::eStop;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g
		std::shared_ptr<Action> m_actionComp; // �A�N�V�����R���|�[�l���g

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_MoveDir; // �ړ�����

		Vec3 m_startPos; // �X�^�[�g�ʒu
		Vec3 m_endPos;   // ��~�ʒu

		float m_speed = 2.0f;

	public:
		MoveFloor(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& scale,
			const Vec3& position,
			const Vec3& movedir
		) :
			GameObject(stage),
			m_position(position),
			m_scale(scale),
			m_MoveDir(movedir),
			m_speed(1.0f)
		{}

		void OnCreate();
		void OnUpdate();

		void SetUp() { // �X�^�[�g�ʒu�ƒ�~�ʒu��ݒ�
			m_startPos = m_position;
			m_endPos = m_position + (m_scale * m_MoveDir);
		}

		// �ړ����̃X�e�[�g�ݒ�p�֐�
		void FloorActive(const bool& active) {
			if (active) {
				eMoveState = EMoveState::eMove;
			}
			else {
				eMoveState = EMoveState::eReMove;
			}
		}

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}