/*!
@file BeltConveyor.h
@brief �x���g�R���x�A�[
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�������̃x���g�R���x�A
	//--------------------------------------------------------------------------------------
	class BeltConveyorLeft : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		BeltConveyorLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorLeft();
		//������
		virtual void OnCreate() override;

		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;

	};
	//--------------------------------------------------------------------------------------
	//	�E�����̃x���g�R���x�A
	//--------------------------------------------------------------------------------------
	class BeltConveyorRight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		BeltConveyorRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorRight();
		//������
		virtual void OnCreate() override;

		//����
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;

	};

}
//end basecross
