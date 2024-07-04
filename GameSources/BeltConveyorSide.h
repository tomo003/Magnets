/*!
@file BeltConveyorSide.��
@brief �x���g�R���x�A�[�̒[
@author �����I
@detail�@�x���g�R���x�A�̗��[�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------
	//�������̃x���g�R���x�A
	//---------------------------------------------------------------
	class BeltConveyorSideLeft : public GameObject {
		Vec3 m_Scale; // �T�C�Y
		Vec3 m_Position; // �ݒu�ʒu
	public:
		//�\�z�Ɣj��
		BeltConveyorSideLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideLeft();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

	//--------------------------------------------------------------
	//�������̃x���g�R���x�A
	//---------------------------------------------------------------
	class BeltConveyorSideRight : public GameObject {
		Vec3 m_Scale; // �T�C�Y
		Vec3 m_Position; // �ݒu�ʒu
	public:
		//�\�z�Ɣj��
		BeltConveyorSideRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideRight();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

}
//end basecross
