/*!
@file BeltConveyor.h
@brief ベルトコンベアーの実装
@author 佐藤悠
@detail　ベルトコンベアの中央部の実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	左方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	class BeltConveyorLeft : public GameObject {
		Vec3 m_Scale; // サイズ
		Vec3 m_Position; // 設置位置
	public:
		//構築と破棄
		BeltConveyorLeft(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorLeft();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};
	//--------------------------------------------------------------------------------------
	//	右方向のベルトコンベア
	//--------------------------------------------------------------------------------------
	class BeltConveyorRight : public GameObject {
		Vec3 m_Scale; // サイズ
		Vec3 m_Position; // 設置位置
	public:
		//構築と破棄
		BeltConveyorRight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~BeltConveyorRight();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

}
//end basecross
