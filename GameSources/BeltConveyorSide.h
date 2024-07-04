/*!
@file BeltConveyorSide.ｈ
@brief ベルトコンベアーの端
@author 佐藤悠
@detail　ベルトコンベアの両端の実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------
	//左方向のベルトコンベア
	//---------------------------------------------------------------
	class BeltConveyorSideLeft : public GameObject {
		Vec3 m_Scale; // サイズ
		Vec3 m_Position; // 設置位置
	public:
		//構築と破棄
		BeltConveyorSideLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideLeft();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

	//--------------------------------------------------------------
	//左方向のベルトコンベア
	//---------------------------------------------------------------
	class BeltConveyorSideRight : public GameObject {
		Vec3 m_Scale; // サイズ
		Vec3 m_Position; // 設置位置
	public:
		//構築と破棄
		BeltConveyorSideRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorSideRight();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};

}
//end basecross
