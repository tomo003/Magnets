/*!
@file SaveObject.h
@brief セーブオブジェクト
@autor 吉田鈴
@detail セーブオブジェクトやその周辺のオブジェクトの実体
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// セーブオブジェクト上の赤い板ポリ
	//--------------------------------------------------------------------------------------
	class SaveTriangleRed :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;        // 線形補間の割合
		float m_rotateSpeed = 3.0f; // 板ポリの回転する速さ
	public:
		// 構築と破棄
		SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleRed();
		// 初期化
		virtual void OnCreate() override;

		/**
		* @brief オブジェクトを回転させる関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void Rotate();

		/**
		* @brief テクスチャを変更する関数
		* @param (Texture) 適応したいテクスチャ名
		* @return 戻り値なし
		*/
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	// セーブオブジェクト上の青い板ポリ
	//--------------------------------------------------------------------------------------
	class SaveTriangleBlue :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;        // 線形補間の割合
		float m_rotateSpeed = 3.0f; // 板ポリの回転する速さ
	public:
		//構築と破棄
		SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleBlue();
		// 初期化
		virtual void OnCreate() override;

		/**
		* @brief オブジェクトを回転させる関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void Rotate();

		/**
		* @brief テクスチャを変更する関数
		* @param (Texture) 適応したいテクスチャ名
		* @return 戻り値なし
		*/
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	// セーブオブジェクト上の文字の板ポリ
	//--------------------------------------------------------------------------------------
	class SavePointTexture :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		// 構築と破棄
		SavePointTexture(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePointTexture();
		// 初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	// セーブポイント
	//--------------------------------------------------------------------------------------
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<SaveTriangleRed> m_ptrTriangleRed;   // SaveTriangleRed
		std::shared_ptr<SaveTriangleBlue> m_ptrTriangleBlue; // SaveTriangleBlue

		bool isCollPlayer = false;  // プレイヤーが通り過ぎたかの判定
		bool isCollPlayer2 = false; // プレイヤー２が通り過ぎたかの判定
	public:
		// 構築と破棄
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		// 初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		/**
		* @brief プレイヤーのセーブ前にリセットする関数
		* @param 引数なし
		* @return 戻り値なし
		*/
		void Reset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};

}
