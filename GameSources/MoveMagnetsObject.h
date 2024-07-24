/*!
* @file MoveMagnetsObject.h
* @brief �ړ����I�u�W�F�N�g�̒�`
* @author ���V�ϖ�
* @details	�������������
*			�{�^���œ�����
*			���p�̃{�^��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//------------------------������������I�u�W�F�N�g------------------------------------------------
	class MoveMetalObject : public GameObject
	{
	public:
		// ���g�̎��ɂ̃X�e�[�g
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
		float m_MagAreaRadius = 4.5f; // ���̓G���A�̔��a
		float m_ratio = 0.0f; // 0 �` 1�̌W��(0 - 100%)

		Vec3 m_position;
		float m_speed; // �ړ��X�s�[�h
		Vec3 m_moveDir;// �ړ�����
		float m_moveVol;// �ړ���

		const array<Vec3, 2> m_points;// ����|�C���g
		int m_currentPointIndex; // ���݂̈ړ����C���ԍ�

	public:
		MoveMetalObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const Vec3& moveDir,
			const float& moveVol) :
			GameObject(stage),
			m_position(position),
			m_moveDir(moveDir),
			m_moveVol(moveVol),
			m_eMagPole(EState::eMetal),
			m_speed(2.0f),
			m_points{Vec3(position + (moveDir * moveVol)), Vec3(position - (moveDir * moveVol))}
		{}

		void OnCreate();
		void OnUpdate();

		/** @brief ���͂̏�Ԃ�int�^�œn��
		*   @fn int GetState()
		*   @param �����Ȃ�
		*   @return int m_eMagPole 
		*   ���͏�Ԃ�int�^�ɃL���X�g���ēn��
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		/** @brief �I�u�W�F�N�g�̏d����n��
		*   @fn float GetMass()
		*   @param �����Ȃ�
		*   @return float �������ɃI�u�W�F�N�g�ɐݒ肵���d��
		*/
		float GetMass() {
			return m_ObjMass;
		}
		/** @brief ���̓G���A�̔��a��n���֐�
		*   @fn float GetAreaRadius()
		*   @param �����Ȃ�
		*   @return float ���̓G���A�̔��a
		*/
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
		void ApplyForceSecondPlayer();
	};
	//------------------------------------------------------------------------------------------------

	//------------------------�������p�̃{�^��--------------------------------------------------------
	class MoveFloorButton : public GameObject 
	{
		// �ғ���Ԃ̃X�e�[�g
		enum class EMoveState {
			eTurnBack, // �߂�
			eStop,   // ��~
			eMove,   // �ړ�
		};

		enum EMoveState eMoveState = EMoveState::eStop; // �����̈ړ���Ԃ͒�~

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_actionComp; //�A�N�V�����R���|�[�l���g

		Vec3 m_position; // ���W
		Vec3 m_scale = Vec3(1.1f, 0.1f, 1.0f); // �T�C�Y

		Vec3 m_startPos; // �X�^�[�g�ʒu
		float m_endPosY; // ��~�ʒu

		float m_speed = 1.0f;


	public:
		MoveFloorButton(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/** @brief �ړ��̊J�n�ʒu�ƒ�~�ʒu�̐ݒ�
		*   @fn void SetUp
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void SetUp() {
			m_startPos  = m_position;
			m_endPosY = m_position.y + m_scale.y;
		}

		/** @brief �v���C���[���{�^���ɏ���Ă��邩�ǂ���
		*   @fn bool PlayerOnButton(const Vec3& hitPoint)
		*   @param hitPoint �v���C���[�ƃ{�^���̐ڐG�ʒu
		*   @return bool �v���C���[���{�^���̏ォ��ڐG���Ă����true
		*/
		bool PlayerOnButton(const Vec3& hitPoint) {
			float scaleYhelf = m_scale.y / 2;
			if (hitPoint.y > m_position.y + scaleYhelf) {
				return true;
			}
			return false;
		}

		/** @brief �ڐG���肪�N���������ɌĂяo�����֐�
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair �ڐG������N�����Ă���I�u�W�F�N�g�y�A
		*   @return �߂�l�Ȃ�
		*/
		void OnCollisionEnter(const CollisionPair& Pair) override;
		/** @brief �ڐG�������Ă��鎞�ɌĂяo�����֐�
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair �ڐG������N�����Ă���I�u�W�F�N�g�y�A
		*   @return �߂�l�Ȃ�
		*/
		//void OnCollisionExcute(const CollisionPair& Pair) override;
		/** @brief �ڐG���肪�Ȃ��Ȃ������ɌĂяo�����֐�
		*   @fn void OnCollisionEnter(const CollisionPair& Pair)
		*   @param Pair �ڐG������N�����Ă���I�u�W�F�N�g�y�A
		*   @return �߂�l�Ȃ�
		*/
		void OnCollisionExit(const CollisionPair& Pair) override;
	};
	//------------------------------------------------------------------------------------------------

	//------------------------�{�^���œ�����--------------------------------------------------------
	class MoveFloor : public GameObject
	{
		// �ғ���Ԃ̃X�e�[�g
		enum class EMoveState {
			eTurnBack, // �߂�
			eStop,   // ��~
			eMove,   // �ړ�
		};

		enum EMoveState eMoveState = EMoveState::eStop; // �����̈ړ���Ԃ͒�~

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g
		std::shared_ptr<Action> m_actionComp; // �A�N�V�����R���|�[�l���g
		shared_ptr<SoundItem> m_kadouonn;

		Vec3 m_position; // ���W
		Vec3 m_scale; // �T�C�Y
		Vec3 m_MoveDir; // �ړ�����

		Vec3 m_startPos; // �X�^�[�g�ʒu
		Vec3 m_endPos;   // ��~�ʒu

		float m_speed = 2.0f; // �ړ��X�s�[�h

		bool MoveSEPlay = false; // �ړ�����SE��炷���ǂ���

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
			m_MoveDir(movedir)
		{}

		void OnCreate();
		void OnUpdate();

		/** @brief ���̈ړ��̏���
		*   @fn void FloorMovePattern()
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void FloorMovePattern();

		/** @brief �ړ��̊J�n�ʒu�ƒ�~�ʒu�̐ݒ�
		*   @fn void SetUp()
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void SetUp() {
			m_startPos = m_position;
			m_endPos = m_position + (m_scale * 0.9f * m_MoveDir);
		}

		/** @brief �ړ����̃X�e�[�g�ݒ�p�֐�
		*   @fn void FloorActive(const bool& active)
		*   @param active ���������Ă���Ȃ�true
		*   @return �߂�l�Ȃ�
		* �@@details active��true�Ȃ�eMove(�ړ�)�Afalse�Ȃ�eTurnBack(�߂�)
		*/
		void FloorActive(const bool& active) {
			if (active) {
				eMoveState = EMoveState::eMove;
			}
			else {
				eMoveState = EMoveState::eTurnBack;
			}
		}

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
		
		/** @brief �v���C���[�����X�|�[���������Ɉʒu�����Z�b�g����֐�(���܂Ɏ~�܂��Ă��܂�����)
		*   @fn void ResetAll()
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void ResetAll();
	};
	//------------------------------------------------------------------------------------------------
}