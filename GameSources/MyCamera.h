/*!
@file MyCamera.h
@brief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�P�l�v���C�p�J����
	class MyCamera :public Camera {

	private:
		weak_ptr<GameObject> m_TargetObj;
	public:
		//�R���X�g���N�^
		MyCamera(){};

		//�f�X�g���N�^
		virtual ~MyCamera(){};

		//�ڕW�I�u�W�F�N�g�𓾂�
		shared_ptr<GameObject> GetPlayerObj() const;

		//�ڕW�I�u�W�F�N�g��ݒ肷��
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		//�J�����̎��_��ݒ肷��
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;
	};

	//�Q�l�v���C�p�J����
	class DuoCamera :public Camera {

	private:
		//�J�����������ŏ��l
		float m_minEyeZ;
		//�J�����������ő�l
		float m_maxEyeZ;

		weak_ptr<GameObject> m_TargetObj;
		weak_ptr<GameObject> m_SecondTargetObj;

	public:
		DuoCamera() :
			m_minEyeZ(-20),
			m_maxEyeZ(-30)
		{}

		//�f�X�g���N�^
		virtual ~DuoCamera(){};

		//�ڕW�I�u�W�F�N�g�𓾂�(�v���C���[�P)
		shared_ptr<GameObject> GetPlayerObj() const;

		//�ڕW�I�u�W�F�N�g�𓾂�(�v���C���[�Q)
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		//�ڕW�I�u�W�F�N�g��ݒ肷��(�v���C���[�P)
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		//�ڕW�I�u�W�F�N�g��ݒ肷��(�v���C���[�Q)
		void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		//�J�����̎��_��ݒ肷��
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;
	};


}
//end basecross

