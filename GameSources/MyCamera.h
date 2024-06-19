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
		weak_ptr<GameObject> m_GoalObj;

		float m_EyeZ = -20.0f;
		float m_zoomEyeZ = -10.0f;
		float m_Height = 0.0f;
		float m_ratio = 0.0f;
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

		void ZoomCamera();
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
		weak_ptr<GameObject> m_StartObj;
		weak_ptr<GameObject> m_GoalObj;

		float m_EyeZ = -20.0f;
		float m_zoomEyeZ = -10.0f;
		float m_Height = 0.0f; 
		float m_PulusHeight = 3.0f;// �����グ��
		float m_ratio = 0.0f;
		float m_startEye = 0.0f;
		float m_startHeight = 0.0f;

		bool isZoomCamera = false;
	public:
		DuoCamera() :
			m_minEyeZ(-22),
			m_maxEyeZ(-27)
		{}

		//�f�X�g���N�^
		virtual ~DuoCamera(){};

		//�ڕW�I�u�W�F�N�g�𓾂�(�v���C���[�P)
		shared_ptr<GameObject> GetPlayerObj() const;

		//�ڕW�I�u�W�F�N�g�𓾂�(�v���C���[�Q)
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		//�ڕW�I�u�W�F�N�g�𓾂�(�X�^�[�g�I�u�W�F�N�g)
		shared_ptr<GameObject> GetStartObj() const;

		//�ڕW�I�u�W�F�N�g��ݒ肷��(�v���C���[�P)
		virtual void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		//�ڕW�I�u�W�F�N�g��ݒ肷��(�v���C���[�Q)
		virtual void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		//�ڕW�I�u�W�F�N�g��ݒ肷��(�X�^�[�g�I�u�W�F�N�g)
		virtual void SetStartObj(const shared_ptr<GameObject>& Obj);

		//�J����̍�����ݒ肷��
		virtual void SetCameraHeight(const float Height);

		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;

		virtual void MoveCamera();

		//�X�e�[�W�J�n���̃J����
		virtual void StartCamera();

		//�S�[�����̉��o�J����
		virtual void ZoomCamera();
	};


}
//end basecross

