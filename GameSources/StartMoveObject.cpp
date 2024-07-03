/*!
@file StartMoveObject.cpp
@brief �Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�J�n���v���C���[���^��ł���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
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

	void StartMoveObject::OnCreate()
	{
		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		// ���΃I�u�W�F�N�g��ǉ�
		m_ptrMagObjS = GetStage()->AddGameObject<ChangeTextureBlock>(Vec3(1.0f), Vec3(ptrStartPos.x-15, ptrStartPos.y + 5, 0.0f), L"MGNETS_TX");
		m_ptrMagObjN = GetStage()->AddGameObject<ChangeTextureBlock>(Vec3(1.0f), Vec3(ptrStartPos.x-10, ptrStartPos.y + 5, 0.0f), L"MGNETN_TX");

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		//�v���C���[�I�u�W�F�N�g�̎擾
		m_ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_ptrPlayer2 = GetStage()->GetSharedGameObject<Player2>(L"Player2");
		//�v���C���[���}�O�l�b�g�̉��Ɉړ�
		m_ptrPlayer->GetComponent<Transform>()->SetPosition(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z);
		m_ptrPlayer2->GetComponent<Transform>()->SetPosition(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z);

		//�J�������X�^�[�g�J�����ɐݒ肵�Ă���
		auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
		ptrDuoCamera->StartCamera();
	}

	void StartMoveObject::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();// �f���^�^�C���̎擾
		float speed = delta * 6.5f;

		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		auto device = App::GetApp()->GetInputDevice();//�R���g���[���[���W�̎擾
		auto firstPad = device.GetControlerVec()[0];
		auto secondPad = device.GetControlerVec()[1];

		auto ptrMagenetPosS = m_ptrMagObjS->GetComponent<Transform>()->GetPosition();
		auto ptrMagenetPosN = m_ptrMagObjN->GetComponent<Transform>()->GetPosition();

		auto ptrStart = GetStage()->GetSharedGameObject<Start>(L"Start");
		auto ptrStartPos = ptrStart->GetComponent<Transform>()->GetPosition();

		//�v���C���[���������Ă�����
		if (!leavePlayer)
		{
			m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerRed_MESH");
			m_ptrPlayer->SetPlayerMagPole(STATE_NONE);
		}
		if (!leavePlayer2)
		{
			m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"Player2Blue_MESH");
			m_ptrPlayer2->SetPlayerMagPole(STATE_NONE);
		}
		//�v���C���[������Ă��Ȃ��ăX�^�[�g�|�W�V�����ɂ��Ƃ���Ă��Ȃ�������
		if (((ptrMagenetPosN.x + ptrMagenetPosS.x)/2) < ptrStartPos.x && !leavePlayer && !leavePlayer2)
		{
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 2.0f);
				MoveSEPlay = true;
			}

			//�v���C���[�̏d�͂�0�ɕύX
			m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
			m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
			//�X�^�[�g�|�W�V�����܂ňړ�������
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y, ptrMagenetPosS.z));
			m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x + speed, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x + speed, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
		}
		//���΂��X�^�[�g�|�W�V�����ɂ��ǂ蒅������
		else if (((ptrMagenetPosN.x + ptrMagenetPosS.x) / 2) >= ptrStartPos.x )
		{
			if (!StopSEPlay)
			{
				XAPtr->Stop(m_kadouonn);
				XAPtr->Start(L"STOP_SE", 0, 3.0f);
				StopSEPlay = true;
				MoveSEPlay = false;
			}
			if (!leavePlayer)
			{
				m_ptrPlayer->GetComponent<Gravity>()->SetGravityVerocityZero();
				m_ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x, ptrMagenetPosS.y - 1, ptrMagenetPosS.z));
			}
			if (!leavePlayer2)
			{
				m_ptrPlayer2->GetComponent<Gravity>()->SetGravityVerocityZero();
				m_ptrPlayer2->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x, ptrMagenetPosN.y - 1, ptrMagenetPosN.z));
			}

			//���͂�ύX������(RB�{�^������������)
			if (firstPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				if (!leavePlayer) {
					leavePlayer = true;
					m_ptrPlayer->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					m_ptrPlayer->SetPlayerMagPole(STATE_NONE);
				}
			}

			if (secondPad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				if (!leavePlayer2) {
					leavePlayer2 = true;
					m_ptrPlayer2->GetComponent<BcPNTBoneModelDraw>()->SetMeshResource(L"PlayerBrack_MESH");
					m_ptrPlayer2->SetPlayerMagPole(STATE_NONE);
				}
			}

		}

		//�v���C���[�����΂��痣�ꂽ��
		if (leavePlayer && leavePlayer2){
			if (!MoveSEPlay)
			{
				m_kadouonn = XAPtr->Start(L"KADOU_SE", 0, 1.0f);
				MoveSEPlay = true;
			}

			//�J�������Q�[���v���C�p�ɕύX
			auto ptrDuoCamera = dynamic_pointer_cast<DuoCamera>(OnGetDrawCamera());
			ptrDuoCamera->MoveCamera();
			//���΂��A���Ă���
			m_ptrMagObjN->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosN.x - speed, ptrMagenetPosN.y, ptrMagenetPosN.z));
			m_ptrMagObjS->GetComponent<Transform>()->SetPosition(Vec3(ptrMagenetPosS.x - speed, ptrMagenetPosS.y, ptrMagenetPosS.z));

			//���΂��Ԃ����玥�΂�����
			if (ptrMagenetPosN.x < -20)
			{
				XAPtr->Stop(m_kadouonn);
				m_ptrMagObjN->OnDestroy();
				m_ptrMagObjS->OnDestroy();
			}
		}
		else {
		}

	}
}