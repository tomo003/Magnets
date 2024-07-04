/*!
@file GoalObject.h
@brief ゴールオブジェクト
@autor 吉田鈴
@detail ゴールオブジェクトやその周辺のオブジェクトの実体
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
		GoalSquareRed::GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		GoalSquareRed::~GoalSquareRed() {}
		//初期化
		virtual void OnCreate() override;
		/**
		* @brief テクスチャを変更する関数
		* @param (Texture) 適応したいテクスチャ名
		* @return 戻り値なし
		*/
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
		GoalSquareBlue::GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		GoalSquareBlue::~GoalSquareBlue() {}
		//初期化
		virtual void OnCreate() override;
		/**
		* @brief テクスチャを変更する関数
		* @param (Texture) 適応したいテクスチャ名
		* @return 戻り値なし
		*/
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//ゴールオブジェクト
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<GoalSquareRed> m_ptrSquareRed;   // GoalSquareRed
		std::shared_ptr<GoalSquareBlue> m_ptrSquareBlue; // GoalSquareBlue

		bool isCollPlayer = false;    // プレイヤーが通り過ぎたかの判定
		bool isCollPlayer2 = false;   // プレイヤー2が通り過ぎたかの判定
		bool isDisplaySprite = false; // スプライトが表示されているかの判定
	public:
		//構築と破棄
		Goal::Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		Goal::~Goal() {}
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		/**
		* @brief プレイヤーのゴール後の処理を行う関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void PlayerGoal();

		/**
		* @brief プレイヤーのゴール前にリセットする関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void GoalReset();

		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};


}
