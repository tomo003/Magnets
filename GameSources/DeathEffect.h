/*!
@file DeathEffect.h
@brief ���S���̃G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DeathEffectImg :public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		float m_moveSpeed = 20.0f;//�G�t�F�N�g���g��k������X�s�[�h
		float m_sec = 0.0f;

	public:
		DeathEffectImg(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~DeathEffectImg();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
	class DeathEffect : public GameObject
	{
		std::shared_ptr<DeathEffectImg> ptrEffect[8];

		std::shared_ptr<Player> m_ptrPlayerF;
		std::shared_ptr<Player2> m_ptrPlayerS;

		float m_speed; // �ړ��̑���
		float m_forward[8]; // �ړ�������\���P�ʃx�N�g��
		Vec3 m_startPos;

		// �v���C���[�ւ̃|�C���^
		std::shared_ptr<GameObject> m_owner;
		std::shared_ptr<Transform> m_ptrOwnerTrans;

		float m_time = 2.0f;
		float m_removeDistance = 6.0f;//�G�t�F�N�g���폜���鋗��
	public:
		DeathEffect(const std::shared_ptr<Stage>& stage, const shared_ptr<GameObject>& owner) :
			GameObject(stage),
			m_speed(0.1f),
			m_owner(owner)
		{
		}
		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross

