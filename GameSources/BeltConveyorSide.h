/*!
@file BeltConveyorSide.��
@brief �x���g�R���x�A�[�̒[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BeltConveyorSideLeft : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		BeltConveyorSideLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideLeft();
		//������
		virtual void OnCreate() override;

		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;
	};

	class BeltConveyorSideRight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		BeltConveyorSideRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideRight();
		//������
		virtual void OnCreate() override;

		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;
	};

}
//end basecross
