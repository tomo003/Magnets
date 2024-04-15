/*!
@file MagnetsObject.h
@brief ���΃I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetsObject : public GameObject
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2 // �r��
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
		MagnetsObject(const std::shared_ptr<Stage>& stage, const Vec3& position, const EState& eState) :
			GameObject(stage),
			m_position(position),
			m_eMagPole(eState)
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
	};

}
//end basecross

