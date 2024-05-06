/*!
@file MyCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//１人プレイ用カメラ
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

		//目標オブジェクトを得る
		shared_ptr<GameObject> GetGoalObj() const;

		//目標オブジェクトを設定する
		void SetGoalObj(const shared_ptr<GameObject>& Obj);

		//カメラの視点を設定する
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;

		void ZoomCamera();
	};

	//２人プレイ用カメラ
	class DuoCamera :public Camera {

	private:
		//カメラを引く最小値
		float m_minEyeZ;
		//カメラを引く最大値
		float m_maxEyeZ;

		weak_ptr<GameObject> m_TargetObj;
		weak_ptr<GameObject> m_SecondTargetObj;
		weak_ptr<GameObject> m_GoalObj;

		float m_EyeZ = -20.0f;
		float m_zoomEyeZ = -10.0f;
		float m_Height = 0.0f;
		float m_ratio = 0.0f;

	public:
		DuoCamera() :
			m_minEyeZ(-20),
			m_maxEyeZ(-30)
		{}

		//デストラクタ
		virtual ~DuoCamera(){};

		//目標オブジェクトを得る(プレイヤー１)
		shared_ptr<GameObject> GetPlayerObj() const;

		//目標オブジェクトを得る(プレイヤー２)
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		//目標オブジェクトを設定する(プレイヤー１)
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		//目標オブジェクトを設定する(プレイヤー２)
		void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		//目標オブジェクトを得る
		shared_ptr<GameObject> GetGoalObj() const;

		//目標オブジェクトを設定する
		void SetGoalObj(const shared_ptr<GameObject>& Obj);

		//カメラの視点を設定する
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;

		void ZoomCamera();
	};


}
//end basecross

