/*!
@file DeathEffect.h
@brief ���S���̃G�t�F�N�g
@autor �g�c��
@detail �v���C���[�̎��S���ɏo���юU��G�t�F�N�g�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �v���C���[���S���ɔ�юU��|��
	//--------------------------------------------------------------------------------------
	class DeathEffectImg :public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		float m_moveSpeed = 20.0f;//�G�t�F�N�g���g��k������X�s�[�h
		float m_sec = 0.0f;

	public:
		// �\�z�Ɣj��
		DeathEffectImg::DeathEffectImg(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Position(Position)
		{
		}
		DeathEffectImg::~DeathEffectImg() {}
		// ������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	// �v���C���[���S���ɔ|������юU�鏈��
	//--------------------------------------------------------------------------------------
	class DeathEffect : public GameObject
	{
		std::shared_ptr<Player> m_ptrPlayerF;
		std::shared_ptr<Player2> m_ptrPlayerS;

		std::shared_ptr<DeathEffectImg> ptrEffect[8]; // �z��̗v�f���͌Ăяo�������G�t�F�N�g�̐�������

		float m_interval; // �G�t�F�N�g�̔�юU��Ԋu
		float m_speed; // �ړ��̑���
		float m_forward[8] = {0.0f}; // �ړ�������\���P�ʃx�N�g���A�z��̗v�f���͌Ăяo�������G�t�F�N�g�̐�������
		Vec3 m_startPos; // �������ꂽ�|�W�V����

		// �v���C���[�ւ̃|�C���^
		std::shared_ptr<GameObject> m_owner;
		std::shared_ptr<Transform> m_ptrOwnerTrans;

		float m_time = 2.0f;
		float m_removeDistance = 6.0f; // �G�t�F�N�g���폜���鋗��
	public:
		// �\�z�Ɣj��
		DeathEffect(const std::shared_ptr<Stage>& stage, const shared_ptr<GameObject>& owner) :
			GameObject(stage),
			m_interval(360/float(size(ptrEffect))),
			m_speed(0.1f),
			m_owner(owner)
		{
		}
		DeathEffect::~DeathEffect() {}
		// ������
		void OnCreate() override;

		void OnUpdate() override;
	};
}
//end basecross

