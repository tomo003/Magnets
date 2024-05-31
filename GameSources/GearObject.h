/*!
@file GearObject.h
@brief �����O�^�I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GearObject : public GameObject
	{

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 0.0f, 1.0f);
		Vec3 m_Rotation;

		float m_RotPerSec = 30; // ��b��30�x��

	public:
		GearObject(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

	class GearObjFloor : public Metal
	{
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole = EState::eMetal;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g
		std::shared_ptr<EffectPlayer> m_efk;

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_position;
		Vec3 m_Sclae = Vec3(3.0f, 0.75f, 1.0f);

	public :
		GearObjFloor(const std::shared_ptr<Stage>& stage, const Vec3& position):
			Metal(stage, m_Sclae, position),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void RotToCenter(const Vec3& center, const float& rotDir);

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();
		void EfkStop();

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}