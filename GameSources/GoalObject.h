/*!
@file GoalObject.h
@brief ゴールオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト上の赤い板ポリ
	//--------------------------------------------------------------------------------------
	class GoalSquareRed : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		//構築と破棄
		GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareRed();
		//初期化
		virtual void OnCreate() override;

		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト上の青い板ポリ
	//--------------------------------------------------------------------------------------
	class GoalSquareBlue : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		//構築と破棄
		GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareBlue();
		//初期化
		virtual void OnCreate() override;

		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<GoalSquareRed> m_ptrSquareRed;
		std::shared_ptr<GoalSquareBlue> m_ptrSquareBlue;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
		bool isDisplaySprite = false;
	public:
		//構築と破棄
		Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Goal();
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		void PlayerGoal();
		void GoalReset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};


}
