/*!
@file BeltConveyorSide.ｈ
@brief ベルトコンベアーの端
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BeltConveyorSideLeft : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//構築と破棄
		BeltConveyorSideLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideLeft();
		//初期化
		virtual void OnCreate() override;

		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;
	};

	class BeltConveyorSideRight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		//構築と破棄
		BeltConveyorSideRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideRight();
		//初期化
		virtual void OnCreate() override;

		//操作
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnUpdate() override;
	};

}
//end basecross
