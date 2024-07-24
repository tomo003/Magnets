/*!
* @file HammerObject.h
* @brief �n���}�[�I�u�W�F�N�g�ނ̒�`
* @author ���V�ϖ�
* @details	�n���}�[�I�u�W�F�N�g�̒�`
*			�n���}�[�̑O���G���A�̔���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class EState {
		eFalse = -1, // ��
		eN = 1, // �m��
		eS = 2, // �r��
		eMetal = 3 // ����
	};

	/**
	* @brief �n���}�[�̃G���A
	* @details �n���}�[���U�艺�낳���ʒu�ɐ���
	*			�v���C���[���G���A���ɂ���Ƃ��̔�����s��
	*/
	class HammerPressArea : public GameObject
	{
		// �R���|�[�l���g�擾�ȗ��p
		shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g
		shared_ptr<CollisionObb> m_CollComp; // �R���W�����R���|�[�l���g

		Vec3 m_position;
		EState m_eMagPole;

		float m_AreaRightLimit; // �G���A�̉E�[
		float m_AreaLeftLimit; // �G���A�̍��[

		// �v���C���[�̃|�C���^
		shared_ptr<Player> m_ptrPlayerN; // Player1
		Vec3 m_PlayerNPos; // Player1�̍��W
		Vec3 m_PlayerNScaleHelf; // Player1�̃T�C�Y�̔���
		shared_ptr<Player2> m_ptrPlayerS; // Player2
		Vec3 m_PlayerSPos; // Player2�̍��W
		Vec3 m_PlayerSScaleHelf; // Player2�̃T�C�Y�̔���

	public:
		HammerPressArea(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position,
			const EState& mag
		) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(mag),
			m_AreaLeftLimit(m_position.x - 1.5f),
			m_AreaRightLimit(m_position.x + 1.5f)
		{}

		void OnCreate() override;

		/**
		* @fn bool AreaInPlayerN()
		* @brief �v���C���[���n���}�[�̃G���A���ɂ��邩���肷��֐�
		* @param �����Ȃ�
		* @return bool �G���A���Ƀv���C���[��������true
		* @details �v���C���[�P�p
		*/
		bool AreaInPlayerN();
		/**
		* @fn bool AreaInPlayerS()
		* @brief �v���C���[���n���}�[�̃G���A���ɂ��邩���肷��֐�
		* @param �����Ȃ�
		* @return bool �G���A���Ƀv���C���[��������true
		* @details �v���C���[2�p
		*/
		bool AreaInPlayerS();
	};


	class HammerObject : public GameObject
	{
		// ����֌W�̃X�e�[�g
		enum class HammerMoveState {
			TurnBack = -1, // �߂�
			Stop = 0, // ��~
			Antic = 1, // �\������(�k����)
			Swing = 2, // �U�艺�낵
		};
		HammerMoveState m_MoveState; // ���݂̃X�e�[�g
		HammerMoveState m_lastMoveState; // ��O�̃X�e�[�g

		// �R���|�[�l���g�擾�ȗ��p
		shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<PNTBoneModelDraw> m_DrawComp; // �h���[�R���|�[�l���g
		shared_ptr<CollisionObb> m_CollComp; // �R���W�����R���|�[�l���g

		Vec3 m_position; // �������Z��̈ʒu
		Vec3 m_CreatePos; // �������ɓ��͂��ꂽ�ʒu
		Vec3 m_posDiff = Vec3(0.0f, 5.0f, 3.8f); // ���͂��ꂽ�ʒu�Ɛ��K�̈ʒu�̍���
		Vec3 m_Rotation; // ��]
		Vec3 m_Scale = Vec3(1.5f, 1.5f, 3.0f); // �T�C�Y
		const float m_PivotLength = 3.625f; // ��]�̒��S(�s�{�b�g)��ς���

		float m_SwingVal = 90.0f; // ��]�p�x
		float m_SwingSpeed = 5.0f; // ��]���x(�p�x�Ɋ|����)

		EState m_eMagPole; // ���ɂ̏��

		float m_SwingStopTime = 1.0f; // �U�艺�낵��̒�~����
		float m_ResetStopTime = 1.5f; //��~�ʒu�ł̒�~����
		float m_StopTime = 1.5f; // ��~����

		float m_CurrentTime = 0.0f; // ���ݒ�~����(���Z���Ă���)

		// �v���C���[�̃|�C���^
		shared_ptr<Player> m_ptrPlayerF; // Player1
		Vec3 m_PlayerFPos; // Player1�̍��W
		shared_ptr<Player2> m_ptrPlayerS; // Player2
		Vec3 m_PlayerSPos; // Player2�̍��W

		// �G���A�̃|�C���^
		shared_ptr<HammerPressArea> m_ptrPressArea; // �Ԃ����͈͂̃G���A
		shared_ptr<MagnetArea> m_MagArea; // ���̓G���A
		float m_MagAreaRadius = 3.5f;

		float m_TrembleRightX; // �U�ꕝ(�E)
		float m_TrembleLeftX; // �U�ꕝ(��)
		int m_TrembleDir = 1; // �k����Ƃ��̕���(�����͐��̒l)
		int m_TrembleSpeed = 10; // �k����Ƃ��̑��x

		shared_ptr<XAudio2Manager> m_ptrAudio; // SE�Đ��pAudioManager�̃|�C���^
		bool isSEActive = false; // �U�艺�낵�̂Ƃ���SE���Đ������ǂ���

	public:
		HammerObject(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position,
			const int& MagPole
		) :
			GameObject(stage),
			m_CreatePos(position),
			m_eMagPole(EState(MagPole)),
			m_MoveState(HammerMoveState::Stop), // �����l�͒�~
			m_lastMoveState(HammerMoveState::TurnBack), // �����l�͖߂�(��~���Ԃ��R�b�ɂ���������)
			m_TrembleRightX(m_position.x + 1.0f), // �h���Ƃ��̉E�[
			m_TrembleLeftX(m_position.x - 1.0f) // �h���Ƃ��̍��[
		{
		}

		void OnCreate() override;
		void OnUpdate() override;


		/** @brief �ڐG���肪�N���������ɌĂяo�����֐�
		*   @fn void OnCollisionEnter(shared_ptr<GameObject>& Other)
		*   @param Other �ڐG������N�����Ă���I�u�W�F�N�g
		*   @return �߂�l�Ȃ�
		*/
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		/**
		* @fn void ChangeFixed(bool fix)
		* @brief �n���}�[�̍��̂�؂�ւ���֐�
		* @param fix ���̂�L���ɂ������Ȃ�true
		* @return �߂�l�Ȃ�
		* @details �n���}�[�����̂̂܂܂��ƃv���C���[�Ƃ̐ڐG���肪���Ȃ����A���̂���Ȃ��ƈʒu���o�O��̂ŉ�����
		*/
		void ChangeFixed(bool fix) {
			m_CollComp->SetFixed(fix);
			if (fix) {
				m_CollComp->SetAfterCollision(AfterCollision::Auto);
			}
			else {
				m_CollComp->SetAfterCollision(AfterCollision::None);
			}
		}

		/**
		* @fn HammerMoveState GetHammerMoveState()
		* @brief �n���}�[�̃X�e�[�g��n��
		* @param �����Ȃ�
		* @return HammerMoveState m_MoveState �n���}�[�̓���X�e�[�g
		*/
		HammerMoveState GetHammerMoveState() {
			return m_MoveState;
		}

		/** 
		* @fn void SetHammerMoveState(const HammerMoveState& hms)
		* @brief �n���}�[�̃X�e�[�g���Z�b�g
		* @param hms �n���}�[�̓���X�e�[�g
		* @return �߂�l�Ȃ�
		*/
		void SetHammerMoveState(const HammerMoveState& hms) {
			m_MoveState = hms;
		}

		/**
		* @fn void SetStopTime(const float time)
		* @brief ��~���Ԃ��Z�b�g
		* @param time �b
		* @return �߂�l�Ȃ�
		*/
		void SetStopTime(const float time) {
			m_StopTime = time;
		}

		/**
		* @fn void ResetCurrentTime()
		* @brief ���݂̌o�ߎ��ԃJ�E���g�����Z�b�g
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ResetCurrentTime() {
			m_CurrentTime = 0.0f;
		}

		/**
		* @fn void TurnBackHammer()
		* @brief �n���}�[�̖߂铮��
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void TurnBackHammer();

		/**
		* @fn void StopHammer(const HammerMoveState& lastState)
		* @brief �n���}�[�̒�~����
		* @param �����@lastState ��O�̃X�e�[�g ���̃X�e�[�g��ݒ肷�邽�߂Ɏg�p
		* @return �߂�l�Ȃ�
		*/
		void StopHammer(const HammerMoveState& lastState);

		/** 
		* @fn void AnticHammer()
		* @brief �n���}�[�̗\������
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void AnticHammer();
		/** 
		* @fn void AnticTremble(const float& time)
		* @brief �\������p�̐U��
		* @param time ����
		* @return �߂�l�Ȃ�
		*/
		void AnticTremble(const float& time);

		/** 
		* @fn void SwingHammer()
		* @brief �n���}�[�̐U�艺�낷����
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void SwingHammer();
		/**
		* @fn void SwingingPlayerCheck()
		* @brief �U�艺�낵���Ƀv���C���[���������̏���
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void SwingingPlayerCheck();

		/** 
		* @fn void MagAreaCorrection()
		* @brief �U�艺�낵���Ɏ��̓G���A��␳����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void MagAreaCorrection();
	};
}