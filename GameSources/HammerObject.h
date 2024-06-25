/*!
* @file HammerObject.h
* @brief �n���}�[�I�u�W�F�N�g
* @author ���V�ϖ�
* @details	�n���}�[�I�u�W�F�N�g
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
		shared_ptr<Player> m_ptrPlayerF; // Player1
		Vec3 m_PlayerFPos; // Player1�̍��W
		Vec3 m_PlayerFScaleHelf; // Player1�̃T�C�Y�̔���
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

		bool AreaInPlayerF();
		bool AreaInPlayerS();
	};


	class HammerObject : public GameObject
	{
		// ����֌W�̃X�e�[�g
		enum class HammerMoveState {
			Remove = -1, // �߂�
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
		Vec3 m_posDiff = Vec3(0.0f, 4.625f, 4.625f); // ���͂��ꂽ�ʒu�Ɛ��K�̈ʒu�̍���
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
			m_lastMoveState(HammerMoveState::Remove), // �����l�͖߂�(��~���Ԃ��R�b�ɂ���������)
			m_TrembleRightX(m_position.x + 0.5f),
			m_TrembleLeftX(m_position.x - 0.5f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		/** @brief �n���}�[�̃X�e�[�g��n��
		*   @param �����Ȃ�
		*   @return �߂�l m_MoveState�@�n���}�[�̓���X�e�[�g
		*/
		HammerMoveState GetHammerMoveState() {
			return m_MoveState;
		}
		/** @brief �n���}�[�̃X�e�[�g���Z�b�g
		*   @param ���� hms �n���}�[�̓���X�e�[�g
		*/
		void SetHammerMoveState(const HammerMoveState& hms) {
			m_MoveState = hms;
		}

		/** @brief ��~���Ԃ��Z�b�g
		*   @param ���� time �b
		*/
		void SetStopTime(const float time) {
			m_StopTime = time;
		}

		// @brief ���݂̌o�ߎ��ԃJ�E���g�����Z�b�g
		void ResetCurrentTime() {
			m_CurrentTime = 0.0f;
		}

		/** @brief �n���}�[�̖߂铮��
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void RemoveHammer();

		/** @brief �n���}�[�̒�~����
		*   @param �����@lastState ��O�̃X�e�[�g
		*				�@���̃X�e�[�g��ݒ肷�邽�߂Ɏg�p
		*   @return �߂�l�Ȃ�
		*/
		void StopHammer(const HammerMoveState& lastState);

		/** @brief �n���}�[�̗\������
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void AnticHammer();
		/** @brief �\������p�̐U��
		*   @param time ����
		*   @return �߂�l�Ȃ�
		*/
		void AnticTremble(const float& time);

		/** @brief �n���}�[�̐U�艺�낷����
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void SwingHammer();
		/** @brief �U�艺�낵���Ƀv���C���[���������̏���
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void SwingingPlayerCheck();

		/** @brief �U�艺�낵���Ɏ��̓G���A�I�u�W�F�N�g��␳����֐�
		*   @param �����Ȃ�
		*   @return �߂�l�Ȃ�
		*/
		void MagAreaCorrection();
	};
}