/*!
@file SaveObject.h
@brief セーブオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//セーブオブジェクト上の赤い板ポリ
	//--------------------------------------------------------------------------------------
	class SaveTriangleRed :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f; // 板ポリの回転する速さ
	public:
		//構築と破棄
		SaveTriangleRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleRed();
		//初期化
		virtual void OnCreate() override;

		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//セーブオブジェクト上の青い板ポリ
	//--------------------------------------------------------------------------------------
	class SaveTriangleBlue :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)

		float m_ratio = 0.0;
		float m_rotateSpeed = 3.0f; // 板ポリの回転する速さ
	public:
		//構築と破棄
		SaveTriangleBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SaveTriangleBlue();
		//初期化
		virtual void OnCreate() override;

		void Rotate();
		void ChangeTexture(wstring Texture);
	};

	//--------------------------------------------------------------------------------------
	//セーブオブジェクト上の文字の板ポリ
	//--------------------------------------------------------------------------------------
	class SavePointTexture :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // 頂点データ
		std::vector<uint16_t> m_indices; // 頂点インデックス(頂点の並び順・組み合わせ)
	public:
		//構築と破棄
		SavePointTexture(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePointTexture();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//セーブポイント
	//--------------------------------------------------------------------------------------
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<SaveTriangleRed> m_ptrTriangleRed;
		std::shared_ptr<SaveTriangleBlue> m_ptrTriangleBlue;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
	public:
		//構築と破棄
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		void Reset();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};

}
