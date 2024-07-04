/*!
* @file MagnetsObject.h
* @brief ���΃I�u�W�F�N�g
* @author �g�c��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	// ���΃I�u�W�F�N�g�̃x�[�X(����)
	class MagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole;	// ���ɂ̏��

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g
 
		float m_ObjMass = 1.0f;

		Vec3 m_position;

		float m_MagAreaRadius = 3.0f;

	public:
		MagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		virtual void OnCreate();
		virtual void OnUpdate();

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

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();
	};

	//--------------------------------------------------------------------------------------
	// N�ɂ̎��΃I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class MagnetN : public GameObject {
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
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
		int m_State;
		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetN::MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		MagnetN::~MagnetN() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
	};

	//--------------------------------------------------------------------------------------
	// S�ɂ̎��΃I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class MagnetS : public GameObject {
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
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetS::MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		MagnetS::~MagnetS() {}
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
	};
}
//end basecross

