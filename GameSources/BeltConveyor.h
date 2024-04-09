/*!
@file BeltConveyor.h
@brief ベルトコンベアー
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	左方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	class BeltConveyorLeft : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//構築と破棄
		BeltConveyorLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorLeft();
		//初期化
		virtual void OnCreate() override;

		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;

	};
	//--------------------------------------------------------------------------------------
	//	右方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	class BeltConveyorRight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//構築と破棄
		BeltConveyorRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorRight();
		//初期化
		virtual void OnCreate() override;

		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;

	};

}
//end basecross
