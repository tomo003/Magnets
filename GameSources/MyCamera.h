/*!
@file MyCamera.h
@brief �Q�[���X�e�[�W�̃J����
@autor �g�c��
@detail �Q�[���X�e�[�W��ł̃v���C���[�Ǐ]�J�����A�Y�[�����o�J�����Ȃǎ���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �Q�l�v���C�p�̃Q�[���X�e�[�W�v���C���̃J����
	//--------------------------------------------------------------------------------------
	class DuoCamera :public Camera {

	private:
		float m_minEyeZ = -22; // �J�����������ŏ��l
		float m_maxEyeZ = -27; // �J�����������ő�l

		weak_ptr<GameObject> m_TargetObj;       // �X�e�[�W�ŒǏ]����I�u�W�F�N�g1
		weak_ptr<GameObject> m_SecondTargetObj; // �X�e�[�W�ŒǏ]����I�u�W�F�N�g2
		weak_ptr<GameObject> m_StartObj;        // �X�^�[�g�I�u�W�F�N�g

		float m_EyeZ = -20.0f;     // �J������Eye��Z���W
		float m_zoomEyeZ = -10.0f; // �J����Zoom���̍ł��߂������ʒu
		float m_Height = 0.0f;     // �J�����̍���
		float m_ratio = 0.0f;      // ���`��Ԃ̊���
		float m_startEyeZ = 0.0f;  // Zoom���n�܂�J�����̈ʒu
		float m_startY = 0.0f;     // Zoom���n�܂�J�����̍���
		float m_distance = 0.3;    // �v���C���[�̋����ƃJ�����������l�̒����p

		bool isZoomCamera = false; // �J������Zoom���n�܂��Ă��邩
	public:
		// �\�z�Ɣj��
		DuoCamera(){}
		virtual ~DuoCamera(){};

		virtual void OnUpdate()override;

		/**
		* @brief �ڕW�I�u�W�F�N�g�𓾂�
		* @param �����Ȃ�
		* @return �߂�l Player�I�u�W�F�N�g
		*/
		shared_ptr<GameObject> GetPlayerObj() const;

		/**
		* @brief �ڕW�I�u�W�F�N�g�𓾂�
		* @param �����Ȃ�
		* @return �߂�l Player2�I�u�W�F�N�g
		*/
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		/**
		* @brief �ڕW�I�u�W�F�N�g�𓾂�
		* @param �����Ȃ�
		* @return �߂�l Start�I�u�W�F�N�g
		*/
		shared_ptr<GameObject> GetStartObj() const;

		/**
		* @brief �ڕW�I�u�W�F�N�g��ݒ肷��
		* @param (obj) m_TargetObj�ɐݒ肵�����I�u�W�F�N�g
		* @return �߂�l�Ȃ�
		*/
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief �ڕW�I�u�W�F�N�g��ݒ肷��
		* @param (obj) m_SecondTargetObj�ɐݒ肵�����I�u�W�F�N�g
		* @return �߂�l�Ȃ�
		*/
		void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief �ڕW�I�u�W�F�N�g��ݒ肷��
		* @param (obj) m_StartObj�ɐݒ肵�����I�u�W�F�N�g
		* @return �߂�l�Ȃ�
		*/
		void SetStartObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief �J�����̍�����ݒ肷��
		* @param (Height) �J�����̍���
		* @return �߂�l�Ȃ�
		*/
		void SetCameraHeight(const float Height);

		/**
		* @brief At��ݒ肷��
		* @param (At) �ݒ肵����At
		* @return �߂�l�Ȃ�
		*/
		virtual void SetAt(const bsm::Vec3& At)override;

		/**
		* @brief Eye��ݒ肷��
		* @param (Eye) �ݒ肵����Eye
		* @return �߂�l�Ȃ�
		*/
		virtual void SetEye(const bsm::Vec3& Eye)override;

		/**
		* @brief �Q�[���v���C���̒ʏ�̃J����
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void MoveCamera();

		/**
		* @brief �X�e�[�W�J�n���̃J����
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void StartCamera();

		/**
		* @brief �S�[�����̃J����
		* @param �����Ȃ�
		* @return �߂�l�Ȃ�
		*/
		void ZoomCamera();
	};
}
//end basecross

