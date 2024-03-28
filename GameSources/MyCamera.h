/*!
@file MyCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera :public Camera {
		weak_ptr<GameObject> m_TargetObj;
	public:
		//コンストラクタ
		MyCamera();

		//デストラクタ
		virtual ~MyCamera();

		//目標オブジェクトを得る
		shared_ptr<GameObject> GetTargetObj() const;

		//目標オブジェクトを設定する
		void SetTargetObj(const shared_ptr<GameObject>& Obj);

		//カメラの視点を設定する
		virtual void SetAt(const bsm::Vec3& At)override;

		virtual void SetEye(const bsm::Vec3& Eye)override;

		virtual void OnUpdate()override;
	};

}
//end basecross

