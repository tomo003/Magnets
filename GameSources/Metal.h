/*!
@file Metal.h
@brief �����I�u�W�F�N�g
@autor 
@detail �X�e�[�W�̔z�u����Ă�������I�u�W�F�N�g�̎���
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Metal : public GameObject {
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

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

	public:
		Metal::Metal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		Metal::~Metal() {}
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		virtual int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		virtual float GetMass() {
			return m_ObjMass;
		}
		virtual float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		virtual Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		virtual void ApplyForcePlayer();
		virtual void ApplyForceSecondPlayer();
	};
}
