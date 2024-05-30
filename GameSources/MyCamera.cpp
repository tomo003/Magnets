/*!
@file MyCamera.cpp
@brief カメラ
*/

#include "stdafx.h"
#include "Project.h"
#include <cstdlib>

namespace basecross {

	shared_ptr<GameObject> MyCamera::GetPlayerObj() const {
		if (!m_TargetObj.expired()) {
			return m_TargetObj.lock();
		}
		return nullptr;
	}

	void MyCamera::SetPlayerObj(const shared_ptr<GameObject>& Obj) {
		m_TargetObj = Obj;
	}

	void MyCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
	}

	void MyCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
	}

	void MyCamera::OnUpdate() {
		auto ptrTarget = GetPlayerObj();
		Vec3 newAt = GetAt();
		newAt = Vec3(ptrTarget->GetComponent<Transform>()->GetWorldPosition().x, m_Height, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3(ptrTarget->GetComponent<Transform>()->GetWorldPosition().x,m_Height , m_EyeZ);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}

	void MyCamera::ZoomCamera() {
		auto& app = App::GetApp();
		//デルタタイム(毎フレームからの経過時間)を取得する
		float delta = app->GetElapsedTime();

		auto ptrTarget = GetPlayerObj();

		Vec3 newAt = GetAt();
		Vec3 newEye = GetEye();
		const float start = -20.0f;
		m_EyeZ = Utility::Lerp(start, m_zoomEyeZ, m_ratio);
		m_Height =Utility::Lerp(0.0f, ptrTarget->GetComponent<Transform>()->GetPosition().y + 1, m_ratio);
		if (m_ratio < 1)
		{
			m_ratio += 0.01;
		}
	}

	//二人プレイ用カメラ
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
		auto ptrTarget = GetPlayerObj();
		auto targetPos = ptrTarget->GetComponent<Transform>()->GetWorldPosition();
		auto ptrSecondTarget = GetSecondPlayerObj();
		auto secondTargetPos = ptrSecondTarget->GetComponent<Transform>()->GetWorldPosition();
		auto targetBetween = abs((targetPos.x - secondTargetPos.x)*0.3f);
		float eyeZ = GetEye().z;
		if (!isZoomCamera && targetBetween < 5)
		{
			m_EyeZ = m_minEyeZ - targetBetween;
		}
		else if (targetBetween > 5)
		{
			m_EyeZ = m_maxEyeZ;
		}

		Vec3 newAt = GetAt();
		newAt = Vec3((targetPos.x+ secondTargetPos.x)/2, m_Height, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3((targetPos.x + secondTargetPos.x) / 2, m_Height, m_EyeZ);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}

	void DuoCamera::StartCamera() {
		auto ptrTarget = GetStartObj();
		Vec3 newAt = GetAt();
		newAt = Vec3(ptrTarget->GetComponent<Transform>()->GetWorldPosition().x, m_Height, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3(ptrTarget->GetComponent<Transform>()->GetWorldPosition().x, m_Height, m_EyeZ);

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
		auto targetBetween = abs((targetPos.x - secondTargetPos.x) * 0.3f);

		Vec3 newAt = GetAt();
		Vec3 newEye = GetEye();
		if (!isZoomCamera)
		{
			m_start = m_minEyeZ - targetBetween;
		}
		m_EyeZ = Utility::Lerp(m_start, m_zoomEyeZ, m_ratio);
		m_Height = Utility::Lerp(0.0f, ((targetPos.y + secondTargetPos.y) / 2 ) +1, m_ratio);
		if (m_ratio < 1)
		{
			m_ratio += 0.01;
		}

		isZoomCamera = true;
	}
}
//end basecross
