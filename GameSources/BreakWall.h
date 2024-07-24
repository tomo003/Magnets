/*!
* @file BreakWall.h
* @brief �����
* @author ���V�ϖ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BreakWall : public GameObject
	{
	private:
		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_TransComp; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTBoneModelDraw> m_DrawComp; // �h���[�R���|�[�l���g
		std::shared_ptr<CollisionObb> m_CollComp; // �R���W�����R���|�[�l���g

		Vec3 m_position;
		Vec3 m_posDiff = Vec3(0.0f, 2.5f, 0.0f);
		Vec3 m_Rotation;
		Vec3 m_scale = Vec3(1.0f, 6.0f, 1.0f);

		bool isBreak = false;
	public:
		BreakWall(
				const std::shared_ptr<Stage>& stage,
				const Vec3& position,
				const Vec3& rotation
			) :
			GameObject(stage),
			m_position(position),
			m_Rotation(rotation)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/** @brief �ڐG���肪�N���������ɌĂяo�����֐�
		*   @fn void OnCollisionEnter(shared_ptr<GameObject>& Other)
		*   @param Other �ڐG������N�����Ă���I�u�W�F�N�g
		*   @return �߂�l�Ȃ�
		*/
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		// abs�֐�(��Βl�����߂�)��Vec3�Ŏg����悤��
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};

}