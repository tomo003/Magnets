/*!
@file GameStage.cpp
@brief 登場時にくっついてくる磁石
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	登場時にくっついてくる磁石
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_kadouonn;

		//磁石
		std::shared_ptr<ChangeTextureBox> m_ptrMagObjS;
		std::shared_ptr<ChangeTextureBox> m_ptrMagObjN;

		//プレイヤーが離れているか
		bool leavePlayer = false;
		bool leavePlayer2 = false;

		bool MoveSEPlay = false;
		bool StopSEPlay = false;

public:
	StartMoveObject(const std::shared_ptr<Stage>&StagePtr,
		const Vec3 & Scale,
		const Vec3 & Position
	);
	virtual ~StartMoveObject();
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	};

}

