/*!
@file MyCamera.cpp
@brief ÉJÉÅÉâ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MyCamera::MyCamera():
		Camera()
	{}

	MyCamera::~MyCamera(){}

	shared_ptr<GameObject> MyCamera::GetTargetObj() const {
		if (!m_TargetObj.expired()) {
			return m_TargetObj.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObj(const shared_ptr<GameObject>& Obj) {
		m_TargetObj = Obj;
	}

	void MyCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
	}

	void MyCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
	}

	void MyCamera::OnUpdate() {
		auto ptrTarget = GetTargetObj();
		Vec3 newAt = GetAt();
		newAt = Vec3(ptrTarget->GetComponent<Transform>()->GetPosition().x, 4.0f, 0.0f);
		Vec3 newEye = GetEye();
		newEye = Vec3(ptrTarget->GetComponent<Transform>()->GetPosition().x,0.0f , -20.0f);

		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();
	}
}
//end basecross
