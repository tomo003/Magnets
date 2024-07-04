/*!
@file DeathEffect.cpp
@brief ���S���̃G�t�F�N�g
@autor �g�c��
@detail �v���C���[�̎��S���ɏo���юU��G�t�F�N�g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void DeathEffectImg::OnCreate()
	{
		// ���_�f�[�^
		m_vertices = {
			//  Position,			   Texture(UV���W)
			{Vec3(-1.0f, +1.0f, 0.0f), Vec2(0.0f, 0.0f)}, // ����:0
			{Vec3(+1.0f, +1.0f, 0.0f), Vec2(1.0f, 0.0f)}, // �E��:1
			{Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f)}, // ����:2
			{Vec3(+1.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f)}, // �E��:3
		};

		// ���_�C���f�b�N�Xs
		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		drawComp->SetTextureResource(L"DEATHEFFECT");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_Position);
		transComp->SetScale(m_Scale);

		SetAlphaActive(true);

		SetDrawLayer(2);
	}

	void DeathEffectImg::OnUpdate()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g�ւ̎Q�Ƃ��擾����
		auto& app = App::GetApp();

		// �f���^�^�C�����擾����
		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		m_sec += delta * m_moveSpeed;
		auto scl = Vec3(pow(sin(m_sec + sin(m_sec + sin(m_sec * 2))), 2));
		transComp->SetScale(scl);
	}

	void DeathEffect::OnCreate()
	{
		m_ptrPlayerF = dynamic_pointer_cast<Player>(m_owner);
		m_ptrPlayerS = dynamic_pointer_cast<Player2>(m_owner);

		// ���̊֐����Ă񂾂̂��v���C���[�P��������
		if (m_ptrPlayerF)
		{
			m_ptrOwnerTrans = m_ptrPlayerF->GetComponent<Transform>();
		}
		// ���̊֐����Ă񂾂̂��v���C���[�Q��������
		else if (m_ptrPlayerS)
		{
			m_ptrOwnerTrans = m_ptrPlayerS->GetComponent<Transform>();
		}

		// DeathEffectImg�̐���
		for (int i = 0; i < 8;i++)
		{
			ptrEffect[i] = GetStage()->AddGameObject<DeathEffectImg>(Vec3(1.0f), m_ptrOwnerTrans->GetWorldPosition());
			m_startPos = m_ptrOwnerTrans->GetWorldPosition();
		}

		SetAlphaActive(true);
	}

	void DeathEffect::OnUpdate()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g�ւ̎Q�Ƃ��擾����
		auto& app = App::GetApp();

		// �f���^�^�C�����擾����
		float delta = app->GetElapsedTime();

		m_time -= delta;
		// ��莞�Ԃ��܂Ń��[�v
		if (m_time > 0)
		{
			for (int i = 0;i < 8;i++)
			{
				auto pos = ptrEffect[i]->GetComponent<Transform>()->GetPosition();
				m_forward[i] = 45 * i;
				pos.x += cos(m_forward[i] * XM_PI / 180) * m_speed;
				pos.y -= sin(m_forward[i] * XM_PI / 180) * m_speed;
				ptrEffect[i]->GetComponent<Transform>()->SetPosition(pos);

				// �J�n���̃|�W�V��������m_removeDistance��藣�ꂽ��
				if ((m_startPos - pos).length() > m_removeDistance)
				{
					for (int j = 0;j < 8;j++)
					{
						GetStage()->RemoveGameObject<DeathEffectImg>(ptrEffect[j]);
					}
					m_ptrPlayerF = dynamic_pointer_cast<Player>(m_owner);
					m_ptrPlayerS = dynamic_pointer_cast<Player2>(m_owner);

					// ���̊֐����Ă񂾂̂��v���C���[�P��������
					if (m_ptrPlayerF)
					{
						m_ptrPlayerF->PlayerDeath();
					}
					// ���̊֐����Ă񂾂̂��̂��v���C���[�Q��������
					else if (m_ptrPlayerS)
					{
						m_ptrPlayerS->PlayerDeath();
					}
					GetStage()->RemoveGameObject<DeathEffect>(GetThis<DeathEffect>());
				}
			}
		}
	}
}
//end basecross
