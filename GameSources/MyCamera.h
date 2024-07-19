/*!
@file MyCamera.h
@brief ゲームステージのカメラ
@autor 吉田鈴
@detail ゲームステージ上でのプレイヤー追従カメラ、ズーム演出カメラなど実体
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// ２人プレイ用のゲームステージプレイ時のカメラ
	//--------------------------------------------------------------------------------------
	class DuoCamera :public Camera {

	private:
		float m_minEyeZ = -22; // カメラを引く最小値
		float m_maxEyeZ = -27; // カメラを引く最大値

		weak_ptr<GameObject> m_TargetObj;       // ステージで追従するオブジェクト1
		weak_ptr<GameObject> m_SecondTargetObj; // ステージで追従するオブジェクト2
		weak_ptr<GameObject> m_StartObj;        // スタートオブジェクト

		float m_EyeZ = -20.0f;     // カメラのEyeのZ座標
		float m_zoomEyeZ = -10.0f; // カメラZoom時の最も近ずいた位置
		float m_Height = 0.0f;     // カメラの高さ
		float m_ratio = 0.0f;      // 線形補間の割合
		float m_startEyeZ = 0.0f;  // Zoomが始まるカメラの位置
		float m_startY = 0.0f;     // Zoomが始まるカメラの高さ
		float m_distance = 0.3;    // プレイヤーの距離とカメラが引く値の調整用

		bool isZoomCamera = false; // カメラのZoomが始まっているか
	public:
		// 構築と破棄
		DuoCamera(){}
		virtual ~DuoCamera(){};

		virtual void OnUpdate()override;

		/**
		* @brief 目標オブジェクトを得る
		* @param 引数なし
		* @return 戻り値 Playerオブジェクト
		*/
		shared_ptr<GameObject> GetPlayerObj() const;

		/**
		* @brief 目標オブジェクトを得る
		* @param 引数なし
		* @return 戻り値 Player2オブジェクト
		*/
		shared_ptr<GameObject> GetSecondPlayerObj() const;

		/**
		* @brief 目標オブジェクトを得る
		* @param 引数なし
		* @return 戻り値 Startオブジェクト
		*/
		shared_ptr<GameObject> GetStartObj() const;

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) m_TargetObjに設定したいオブジェクト
		* @return 戻り値なし
		*/
		void SetPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) m_SecondTargetObjに設定したいオブジェクト
		* @return 戻り値なし
		*/
		void SetSecondPlayerObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief 目標オブジェクトを設定する
		* @param (obj) m_StartObjに設定したいオブジェクト
		* @return 戻り値なし
		*/
		void SetStartObj(const shared_ptr<GameObject>& Obj);

		/**
		* @brief カメラの高さを設定する
		* @param (Height) カメラの高さ
		* @return 戻り値なし
		*/
		void SetCameraHeight(const float Height);

		/**
		* @brief Atを設定する
		* @param (At) 設定したいAt
		* @return 戻り値なし
		*/
		virtual void SetAt(const bsm::Vec3& At)override;

		/**
		* @brief Eyeを設定する
		* @param (Eye) 設定したいEye
		* @return 戻り値なし
		*/
		virtual void SetEye(const bsm::Vec3& Eye)override;

		/**
		* @brief ゲームプレイ中の通常のカメラ
		* @param 引数なし
		* @return 戻り値なし
		*/
		void MoveCamera();

		/**
		* @brief ステージ開始時のカメラ
		* @param 引数なし
		* @return 戻り値なし
		*/
		void StartCamera();

		/**
		* @brief ゴール時のカメラ
		* @param 引数なし
		* @return 戻り値なし
		*/
		void ZoomCamera();
	};
}
//end basecross

