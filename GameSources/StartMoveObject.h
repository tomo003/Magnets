/*!
@file GameStage.cpp
@brief “oê‚É‚­‚Á‚Â‚¢‚Ä‚­‚é¥Î
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	“oê‚É‚­‚Á‚Â‚¢‚Ä‚­‚é¥Î
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_kadouonn;

		//¥Î
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjS;
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjN;

		//ƒvƒŒƒCƒ„[‚ª—£‚ê‚Ä‚¢‚é‚©
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

