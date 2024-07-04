/*!
@file StartMoveObject.h
@brief �Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
@autor �g�c��
@detail �Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g��o�ꎞ�̃v���C���[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_operationSound; // �ғ����𗬂����߂̃A�C�e��

		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjS; // ChangeTextureBlock(���������̎��΃I�u�W�F�N�g)
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjN; // ChangeTextureBlock(���������̎��΃I�u�W�F�N�g)

		std::shared_ptr<Player> m_ptrPlayer;   // Player
		std::shared_ptr<Player2> m_ptrPlayer2; // Player2

		bool leavePlayer = false;  // �v���C���[�����΂��痣��Ă��邩
		bool leavePlayer2 = false; // �v���C���[2�����΂��痣��Ă��邩

		bool OperationSEPlay = false; // �ғ���������Ă��邩�̔���
		bool StopSEPlay = false;      // �����~�܂��Ă��邩�̔���

public:
	// �\�z�Ɣj��
	StartMoveObject::StartMoveObject(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	StartMoveObject::~StartMoveObject() {}
	// ������
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	};

}

