/*!
@file GameObjectSample.h
@brief CSVファイル読み込み確認用仮オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class GameObjectSample : public GameObject{
		Vec3 m_Position;
	public:
		GameObjectSample(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		virtual void OnCreate() override;
	};

	class MagnetN : public GameObject {
		Vec3 m_Position;
	public:
		MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		virtual void OnCreate() override;
	};

	class MagnetS : public GameObject {
		Vec3 m_Position;
	public:
		MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		virtual void OnCreate() override;
	};

	class Metal : public GameObject {
		Vec3 m_Position;
	public:
		Metal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		virtual void OnCreate() override;
	};


}
//end basecross
