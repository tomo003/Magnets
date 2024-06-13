/*!
@file GoalObject.h
@brief ゴールオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//ゴール、リスポーン地点の上の四角赤
	class GoalSquareRed : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareRed();
		virtual void OnCreate() override;
		void ChangeTexture(wstring Texture);
	};

	//ゴール、リスポーン地点の上の四角青
	class GoalSquareBlue : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareBlue();
		virtual void OnCreate() override;
		void ChangeTexture(wstring Texture);
	};

	//ゴールオブジェクト
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<GoalSquareRed> m_ptrSquareRed;
		std::shared_ptr<GoalSquareBlue> m_ptrSquareBlue;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
		bool isDisplaySprite = false;
	public:
		Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Goal();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void PlayerGoal();
		void GoalReset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};


}
