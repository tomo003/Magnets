/*!
@file GameObjectSample.h
@brief CSVファイル読み込み確認用仮オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//地面オブジェクト
	class GameObjectSample : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		GameObjectSample(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GameObjectSample();
		virtual void OnCreate() override;
	};

	//N極のオブジェクト
	class MagnetN : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

	private:
		enum EState m_eMagPole;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント

		std::shared_ptr<GameObject> m_ptrArea;

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 5.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
		int m_State;
		std::shared_ptr<EffectPlayer> m_efk;
	public:
		MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
			//const int State
		);
		virtual ~MagnetN();
		virtual void OnCreate() override;
		virtual void OnUpdate();


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();
		void EfkStop();
	};

	//S極のオブジェクト
	class MagnetS : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

	private:
		enum EState m_eMagPole;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 5.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<EffectPlayer> m_efk;
	public:
		MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~MagnetS();
		virtual void OnCreate() override;
		virtual void OnUpdate();


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void EfkStop();
	};

	//金属のオブジェクト
	class Metal : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // 無
			eN = 1, // Ｎ極
			eS = 2, // Ｓ極
			eMetal = 3 // 金属
		};

	private:
		enum EState m_eMagPole;

		// コンポーネント取得省略用
		std::shared_ptr<Transform> m_ptrTrans; // トランスフォームコンポーネント
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // ドローコンポーネント

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		Metal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Metal();
		virtual void OnCreate() override;
		virtual void OnUpdate();


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

	};

	//スタートオブジェクト
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		Start(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Start();
		virtual void OnCreate() override;
	};

	//ゴールオブジェクト
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

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
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

	//セーブポイント
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		virtual void OnCreate() override;
	};


}
//end basecross
