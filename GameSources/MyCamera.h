/*!
@file MyCamera.h
@brief ゲームステージのカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//１人プレイ用のゲームステージプレイ時のカメラ
	//--------------------------------------------------------------------------------------
	class MyCamera :public Camera {

	private:
		weak_ptr<GameObject> m_TargetObj;
		weak_ptr<GameObject> m_GoalObj;

		float m_EyeZ = -20.0f;
		float m_zoomEyeZ = -10.0f;
		float m_Height = 0.0f;
		float m_ratio = 0.0f;
	public:
		//コンストラクタ
		MyCamera(){};

		//デストラクタ
		virtual ~MyCamera(){};

		//目標オブジェクトを得る
		shared_ptr<GameObject> GetPlayerObj() const;

		//目標オブジェクトを設定する
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		//カメラの視点を設定する
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;

		void ZoomCamera();
	};

	//--------------------------------------------------------------------------------------
	//２人プレイ用のゲームステージプレイ時のカメラ
	//--------------------------------------------------------------------------------------
	class DuoCamera :public Camera {

	private:
		//カメラを引く最小値
		float m_minEyeZ;
		//カメラを引く最大値
		float m_maxEyeZ;

		weak_ptr<GameObject> m_TargetObj;
		weak_ptr<GameObject> m_SecondTargetObj;
		weak_ptr<GameObject> m_StartObj;
		weak_ptr<GameObject> m_GoalObj;

		float m_EyeZ = -20.0f;
		float m_zoomEyeZ = -10.0f;
		float m_Height = 0.0f; 
		float m_PulusHeight = 3.0f;// 高さ上げる
		float m_ratio = 0.0f;
		float m_startEye = 0.0f;
		float m_startHeight = 0.0f;

		bool isZoomCamera = false;
	public:
		DuoCamera() :
			m_minEyeZ(-22),
			m_maxEyeZ(-27)
		{}

		//デストラクタ
		virtual ~DuoCamera(){};

		/**
		* @brief 目標オブジェクトを得る
		*/
		shared_ptr<GameObject> GetPlayerObj() const;

		/**
		* @brief 目標オブジェクトを得る
		*/
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		/**
		* @brief 目標オブジェクトを得る
		*/
		shared_ptr<GameObject> GetStartObj() const;

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) 設定したいオブジェクト
		*/
		virtual void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) 設定したいオブジェクト
		*/
		virtual void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) 設定したいオブジェクト
		*/
		virtual void SetStartObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief カメラの高さを設定する
		* @param (Height) カメラの高さ
		*/
		virtual void SetCameraHeight(const float Height);

		/**
		* @brief Atを設定する
		* @param (At) 設定したいAt
		*/
		virtual void SetAt(const bsm::Vec3& At)override;

		/**
		* @brief Eyeを設定する
		* @param (Eye) 設定したいEye
		*/
		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;

		/**
		* @brief ゲームプレイ中の通常のカメラ
		*/
		virtual void MoveCamera();

		/**
		* @brief ステージ開始時のカメラ
		*/
		virtual void StartCamera();

		/**
		* @brief ゴール時のカメラ
		*/
		virtual void ZoomCamera();
	};


}
//end basecross

