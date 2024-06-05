/*!
* @file GearObject.h
* @brief ���ԃI�u�W�F�N�g
* @author ���V�ϖ�
* @details ���ԃI�u�W�F�N�g�Ǝ��Ԃɕt�����Ă��鏰
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class GearObjFloor : public Metal;
	//--------------------------------------------------------------------------------------
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
		shared_ptr<EffectPlayer> m_efk;

		float m_ObjMass = 1.0f; // �I�u�W�F�N�g�̏d��(���͂Ŏg�p)
		float m_MagAreaRadius = 5.0f; // ���͂�K�p����͈�

		Vec3 m_position;
		float m_posDiff = 4.5f;
		Vec3 m_Rotation = Vec3(0.0f);
		Vec3 m_Scale = Vec3(3.5f, 1.0f, 1.0f);

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

		/*!
		@brief �Փ˂����u�ԂɌĂяo�����֐�
		@param �R���W�����y�A(�R���W�������)
		*/
		//void OnCollisionEnter(const CollisionPair& Pair) override;
		//void OnCollisionExcute(const CollisionPair& Pair) override;
		//void OnCollisionExit(const CollisionPair& Pair) override;

		/**
		* @brief ���S�����Ƃɉ�]����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void RotToCenter();

		/**
		* @brief ���͏�Ԃ�n���֐�
		* @param�@�����Ȃ�
		* @return int enum��int�^�ɂ��ēn��
		*/
		int GetState() {
			return static_cast<int>(m_eMagPole);
		}

		/**
		* @brief �I�u�W�F�N�g�̏d����n���֐��j
		* @param �����Ȃ�
		* @return float �I�u�W�F�N�g�̏d��
		*/
		float GetMass() {
			return m_ObjMass;
		}

		/**
		* @brief ���C�G���A�͈̔͂�n���֐��j
		* @param �����Ȃ�
		* @return float ���C�G���A�̔��a
		*/
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		/**
		* @brief �v���C���[�Ɏ��͂�K�p����֐�
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ApplyForcePlayer();

		/**
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
	//	class GearObject : public GameObject;
	//--------------------------------------------------------------------------------------
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

		// �R���|�[�l���g�擾�ȗ��p
		shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.2f); // ������Ƃ������ɔz�u
		Vec3 m_Rotation = Vec3(0.0f);

		float m_RotSpeed = 50; // ��b��50�x��
		int m_RotDir; // ��]����(1 = ����]�A-1 = �E��])
	public:
		GearObject(
			const std::shared_ptr<Stage>& stage, 
			const Vec3& position, 
			const int& RotDir,
			const int& fisetFloorState,
			const int& secondFloorState
			) :
			GameObject(stage),
			m_position(position),
			m_RotDir(RotDir),
			m_eFloorStateF(fisetFloorState),
			m_eFloorStateS(secondFloorState)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};
}