/*!
@file GameStage.cpp
@brief �o�ꎞ�ɂ������Ă��鎥��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�o�ꎞ�ɂ������Ă��鎥��
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		//�X�^�[�g�I�u�W�F�N�g
		std::shared_ptr<Start> m_ptrStart;
		//�v���C���[
		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;
		//����
		std::shared_ptr<MagnetS> m_ptrMagObjS;
		std::shared_ptr<MagnetN> m_ptrMagObjN;

		//�v���C���[������Ă��邩
		bool leavePlayer = false;
		bool leavePlayer2 = false;

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

