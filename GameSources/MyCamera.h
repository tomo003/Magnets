/*!
@file MyCamera.h
@brief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera :public Camera {
		weak_ptr<GameObject> m_TargetObj;
	public:
		//�R���X�g���N�^
		MyCamera();

		//�f�X�g���N�^
		virtual ~MyCamera();

		//�ڕW�I�u�W�F�N�g�𓾂�
		shared_ptr<GameObject> GetTargetObj() const;

		//�ڕW�I�u�W�F�N�g��ݒ肷��
		void SetTargetObj(const shared_ptr<GameObject>& Obj);

		//�J�����̎��_��ݒ肷��
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;
	};

}
//end basecross

