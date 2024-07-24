/*!
* @file GearObject.h
* @brief ���ԃI�u�W�F�N�g
* @author ���V�ϖ�
* @details ���ԃI�u�W�F�N�g�Ǝ��Ԃɕt�����Ă��鏰
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	//----------------���ԃI�u�W�F�N�g�̏�-------------------------------------------
	class GearObjFloor : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole;

		// �R���|�[�l���g�擾�ȗ��p
		shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_ObjMass = 1.0f; // �I�u�W�F�N�g�̏d��(���͂Ŏg�p)
		float m_MagAreaRadius = 3.0f; // ���͂�K�p����͈�

		Vec3 m_position; // �ʒu
		Vec3 m_posDiff = Vec3(0.0f, 4.5f, 0.0f); // �������̈ʒu���琳�K�̈ʒu�܂ł̍���
		Vec3 m_Rotation = Vec3(0.0f); // ��]�̓[��
		Vec3 m_Scale = Vec3(3.5f, 1.0f, 1.0f); // �T�C�Y

		float m_RotSpeed; // ��]�X�s�[�h
		int m_RotDir; // ��]����
	public :
		GearObjFloor(
			const std::shared_ptr<Stage>& stage,
			const Vec3& position, // �ʒu
			const float& RotSpeed, // ��]�X�s�[�h
			const int& RotDir, // ��]����
			const int& state
		):
			GameObject(stage),
			m_position(position),
			m_RotSpeed(RotSpeed),
			m_RotDir(RotDir),
			m_eMagPole(static_cast<EState>(state))
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/**
		* @fn void RotToCenter()
		* @brief ���S�����Ƃɉ�]����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void RotToCenter();

		/**
		* @fn void RotToCenter()
		* @brief ���͏�Ԃ�n���֐�
		* @param�@�����Ȃ�
		* @return int enum��int�^�ɂ��ēn��
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}

		/**
		* @fn float GetMass()
		* @brief �I�u�W�F�N�g�̏d����n���֐�
		* @param �����Ȃ�
		* @return float �I�u�W�F�N�g�̏d��
		*/
		float GetMass() {
			return m_ObjMass;
		}

		/**
		* @fn float GetAreaRadius()
		* @brief ���C�G���A�͈̔͂�n���֐�
		* @param �����Ȃ�
		* @return float ���C�G���A�̔��a
		*/
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		/**
		* @fn void ApplyForcePlayer()
		* @brief �v���C���[�Ɏ��͂�K�p����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ApplyForcePlayer();

		/**
		* @fn void ApplyForceSecondPlayer()
		* @brief �v���C���[�Ɏ��͂�K�p����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ApplyForceSecondPlayer();

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
	//--------------------------------------------------------------------------------------

	//----------------���ԃI�u�W�F�N�g------------------------------------------------------
	class GearObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		// GameeObject�i�[�p�|�C���^
		shared_ptr<GearObjFloor> m_ptrGearFloorF;
		shared_ptr<GearObjFloor> m_ptrGearFloorS;

		int m_eFloorStateF; 
		int m_eFloorStateS;

		float m_floorDiffY = 4.0f;

		// �R���|�[�l���g�擾�ȗ��p
		shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.2f); // ������Ƃ������ɔz�u
		Vec3 m_Rotation = Vec3(0.0f);
		Vec3 m_Scale = Vec3(7.0f);

		float m_RotSpeed; // ��b��50�x��
		int m_RotDir; // ��]����(1 = ����]�A-1 = �E��])
	public:
		GearObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const int& RotDir,
			const float& RotSpeed,
			const int& fisetFloorState,
			const int& secondFloorState
			) :
			GameObject(stage),
			m_position(position),
			m_RotDir(RotDir), // ��]����
			m_RotSpeed(RotSpeed), // �b�ԉ��x��]���邩(Deg)
			m_eFloorStateF(fisetFloorState), // ��ڂ̏��̑���
			m_eFloorStateS(secondFloorState) // ��ڂ̏��̑���
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};
	//--------------------------------------------------------------------------------------
}