/*!
@file StartMoveObject.h
@brief ゲームステージ開始時プレイヤーを運んでくるオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージ開始時プレイヤーを運んでくるオブジェクト
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_kadouonn;

		//磁石
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjS;
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjN;

		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;

		//プレイヤーが離れているか
		bool leavePlayer = false;
		bool leavePlayer2 = false;

		bool MoveSEPlay = false;
		bool StopSEPlay = false;

public:
	//構築と破棄
	StartMoveObject(const std::shared_ptr<Stage>&StagePtr,
		const Vec3 & Scale,
		const Vec3 & Position
	);
	virtual ~StartMoveObject();
	//初期化
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	};

}

