/*!
@file BeltConveyor.h
@brief �x���g�R���x�A�[�̎���
@author �����I
@detail�@�x���g�R���x�A�̒������̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�������̃x���g�R���x�A
	//--------------------------------------------------------------------------------------
	class BeltConveyorLeft : public GameObject {
		Vec3 m_Scale; // �T�C�Y
		Vec3 m_Position; // �ݒu�ʒu
	public:
		//�\�z�Ɣj��
		BeltConveyorLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorLeft();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};
	//--------------------------------------------------------------------------------------
	//	�E�����̃x���g�R���x�A
	//--------------------------------------------------------------------------------------
	class BeltConveyorRight : public GameObject {
		Vec3 m_Scale; // �T�C�Y
		Vec3 m_Position; // �ݒu�ʒu
	public:
		//�\�z�Ɣj��
		BeltConveyorRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorRight();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

}
//end basecross
