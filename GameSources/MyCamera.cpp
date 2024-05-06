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

	shared_ptr<GameObject> MyCamera::GetGoalObj() const {
		if (!m_GoalObj.expired()) {
			return m_GoalObj.lock();
		}
		return nullptr;
	}

	void MyCamera::SetGoalObj(const shared_ptr<GameObject>& Obj) {
		m_GoalObj = Obj;
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
		auto ptrGoal = GetGoalObj();

		Vec3 newAt = GetAt();
		Vec3 newEye = GetEye();
		const float start = -20.0f;
		const float sub = m_zoomEyeZ - start;
		m_EyeZ = Utility::Lerp(start, m_zoomEyeZ, m_ratio);
		m_Height =Utility::Lerp(0.0f, ptrGoal->AddComponent<Transform>()->GetPosition().y + 1,m_ratio);
		if (m_ratio < 1)
		{
			m_ratio += 0.01;
		}

		newEye = Vec3(ptrGoal->GetComponent<Transform>()->GetWorldPosition().x, m_Height, m_EyeZ);
		SetEye(newEye);
		Camera::OnUpdate();
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

	void DuoCamera::SetPlayerObj(const shared_ptr<GameObject>& Obj) {
		m_TargetObj = Obj;
	}

	void DuoCamera::SetSecondPlayerObj(const shared_ptr<GameObject>& Obj) {
		m_SecondTargetObj = Obj;
	}

	shared_ptr<GameObject> DuoCamera::GetGoalObj() const {
		if (!m_GoalObj.expired()) {
			return m_GoalObj.lock();
		}
		return nullptr;
	}

	void DuoCamera::SetGoalObj(const shared_ptr<GameObject>& Obj) {
		m_GoalObj = Obj;
	}

	void DuoCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
	}

	void DuoCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
	}

	void DuoCamera::OnUpdate() {
		auto ptrTarget = GetPlayerObj();
		auto targetPos = ptrTarget->GetComponent<Transform>()->GetPosition();
		auto ptrSecondTarget = GetSecondPlayerObj();
		auto secondTargetPos = ptrSecondTarget->GetComponent<Transform>()->GetPosition();
		auto targetBetween = abs((targetPos.x - secondTargetPos.x)*0.3f);
		float eyeZ = GetEye().z;

		//if (eyeZ > m_maxEyeZ)
		//{
		//	//MessageBox(0, L"DuoCamera", 0, 0);
		//	eyeZ - targetBetween;
		//}
		//else
		//{
		//	eyeZ = m_maxEyeZ;
		//}
		if (GetEye().z < -25.0f)
		{
			eyeZ = -25.0f;
		}

		Vec3 newAt = GetAt();
		newAt = Vec3((targetPos.x+ secondTargetPos.x)/2, 0.0f, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3((targetPos.x + secondTargetPos.x) / 2, 0.0f, -15-targetBetween); 

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}

	void DuoCamera::ZoomCamera() {

	}
}
//end basecross
