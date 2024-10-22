/*!
@file MyCamera.cpp
@brief ゲームステージのカメラ
@autor 吉田鈴 
@detail ゲームステージ上でのプレイヤー追従カメラ、ズーム演出カメラなど実装
*/

#include "stdafx.h"
#include "Project.h"
#include <cstdlib>

namespace basecross {

	shared_ptr<GameObject> DuoCamera::GetPlayerObj() const {
		if (!m_TargetObj.expired()) {
			return m_TargetObj.lock();
		}
		return nullptr;
	}

	shared_ptr<GameObject> DuoCamera::GetSecondPlayerObj() const {
		if (!m_SecondTargetObj.expired()) {
			return m_SecondTargetObj.lock();
		}
		return nullptr;
	}

	shared_ptr<GameObject> DuoCamera::GetStartObj() const {
		if (!m_StartObj.expired()) {
			return m_StartObj.lock();
		}
		return nullptr;
	}

	void DuoCamera::SetPlayerObj(const shared_ptr<GameObject>& Obj) {
		m_TargetObj = Obj;
	}

	void DuoCamera::SetSecondPlayerObj(const shared_ptr<GameObject>& Obj) {
		m_SecondTargetObj = Obj;
	}

	void DuoCamera::SetStartObj(const shared_ptr<GameObject>& Obj) {
		m_StartObj = Obj;
	}

	void DuoCamera::SetCameraHeight(const float Height) {
		m_Height = Height;
	}

	void DuoCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
	}

	void DuoCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
	}

	void DuoCamera::OnUpdate() {
		MoveCamera();
	}

	void DuoCamera::MoveCamera() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto ptrTarget = GetPlayerObj();
		auto targetPos = ptrTarget->GetComponent<Transform>()->GetWorldPosition();
		auto ptrSecondTarget = GetSecondPlayerObj();
		auto secondTargetPos = ptrSecondTarget->GetComponent<Transform>()->GetWorldPosition();
		auto targetBetween = abs(targetPos.x - secondTargetPos.x);
		auto pullDistance = targetBetween * m_distance;
		auto maxBetween =  abs(m_minEyeZ- m_maxEyeZ);// カメラが引く最大値
		float eyeZ = GetEye().z;
		// カメラがズーム状態ではなく、カメラを引く距離がカメラを引く最大値より小さかったら
		if (!isZoomCamera && pullDistance < maxBetween)
		{
			m_EyeZ = m_minEyeZ - pullDistance;
		}
		// カメラを引く距離がカメラを引く最大値より大きかったら
		else if (pullDistance > maxBetween)
		{
			m_EyeZ = m_maxEyeZ;
		}

		Vec3 newAt = GetAt();
		newAt = Vec3((targetPos.x + secondTargetPos.x) / 2, m_Height, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3((targetPos.x + secondTargetPos.x) / 2, m_Height, m_EyeZ);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}

	void DuoCamera::StartCamera() {
		auto ptrTarget = GetPlayerObj();
		auto targetPos = ptrTarget->GetComponent<Transform>()->GetWorldPosition();
		auto ptrSecondTarget = GetSecondPlayerObj();
		auto secondTargetPos = ptrSecondTarget->GetComponent<Transform>()->GetWorldPosition();
		auto targetBetween = abs(targetPos.x - secondTargetPos.x);
		auto ptrStart = GetStartObj();
		m_EyeZ = m_minEyeZ - targetBetween;
		Vec3 newAt = GetAt();
		newAt = Vec3(ptrStart->GetComponent<Transform>()->GetWorldPosition().x, m_Height, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3(ptrStart->GetComponent<Transform>()->GetWorldPosition().x, m_Height, m_EyeZ);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();

	}

	void DuoCamera::ZoomCamera() {
		auto& app = App::GetApp();
		//デルタタイム(毎フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		auto ptrTarget = GetPlayerObj();
		auto targetPos = ptrTarget->GetComponent<Transform>()->GetWorldPosition();
		auto ptrSecondTarget = GetSecondPlayerObj();
		auto secondTargetPos = ptrSecondTarget->GetComponent<Transform>()->GetWorldPosition();
		auto targetBetween = abs(targetPos.x - secondTargetPos.x);
		auto pullDistance = targetBetween * m_distance;

		Vec3 newAt = GetAt();
		Vec3 newEye = GetEye();
		// ズームが始まっていなかったら
		if (!isZoomCamera)
		{
			m_startEyeZ = m_minEyeZ - targetBetween;
			m_startY = m_Height;
			isZoomCamera = true;
		}
		m_EyeZ = Utility::Lerp(m_startEyeZ, m_zoomEyeZ, m_ratio); // スタートのZからZoom後のZまで線形補間関数
		m_Height = Utility::Lerp(m_startY, ((targetPos.y + secondTargetPos.y) / 2 ) +1, m_ratio); // スタートの高さから終わりの高さまで線形補間関数
		// 線形補間の割合が1以下だったら
		if (m_ratio < 1)
		{
			m_ratio += 0.01;
		}
		newAt = Vec3((targetPos.x + secondTargetPos.x) / 2, m_Height, 0.0f);
		newEye = Vec3((targetPos.x + secondTargetPos.x) / 2, m_Height, m_EyeZ);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}
}
//end basecross
