/*!
@file StartMoveObject.h
@brief �Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_kadouonn;

		//����
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjS;
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjN;

		std::shared_ptr<Player> m_ptrPlayer;
		std::shared_ptr<Player2> m_ptrPlayer2;

		//�v���C���[������Ă��邩
		bool leavePlayer = false;
		bool leavePlayer2 = false;

		bool MoveSEPlay = false;
		bool StopSEPlay = false;

public:
	//�\�z�Ɣj��
	StartMoveObject(const std::shared_ptr<Stage>&StagePtr,
		const Vec3 & Scale,
		const Vec3 & Position
	);
	virtual ~StartMoveObject();
	//������
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	};

}

