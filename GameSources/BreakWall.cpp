/*!
* @file BreakWall.cpp
* @brief ����ǂ̎���
* @author ���V�ϖ�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// ����
	void BreakWall::OnCreate()
	{
		m_TransComp = GetComponent<Transform>();
		m_TransComp->SetScale(m_scale);
		m_TransComp->SetRotation(m_Rotation);
		m_position += m_posDiff;
		m_TransComp->SetPosition(m_position);

		m_CollComp = AddComponent<CollisionObb>();

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.5f, 0.125f, 0.8f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		m_DrawComp = AddComponent<PNTBoneModelDraw>();
		m_DrawComp->SetMeshResource(L"BreakWall_MESH");
		m_DrawComp->SetMeshToTransformMatrix(spanMat);

		// �A�j���[�V�����̓o�^
		m_DrawComp->AddAnimation(L"BREAK", 0, 15, false, 10); // ����
		m_DrawComp->AddAnimation(L"BROKEN", 15, 1, true, 1); // �j���

		AddTag(L"BreakWall"); // �j��\�ǂ̃^�O������
	}

	// �X�V
	void BreakWall::OnUpdate() {
		float delta = App::GetApp()->GetElapsedTime();

		m_TransComp->SetPosition(m_position);

		// �j��t���O��true�̂Ƃ�
		if (isBreak) {
			// �A�j���[�V�������Đ�����
			// UpdateAnimation�̓A�j���[�V�������I�����Ă�����true��Ԃ�
			if (m_DrawComp->UpdateAnimation(delta)) {
				// �A�j���[�V�������I�����Ă�����`��ƍX�V���~�߂�
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

	}

	// �ڐG����
	void BreakWall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		// �Փ˂����I�u�W�F�N�g���v���C���[�ɃL���X�g
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto ptrPlayer2 = dynamic_pointer_cast<Player2>(Other);

		// �v���C���[��������Ԃ��̃t���O���󂯎��p�̃t���O(false�ŏ�����)
		bool PlayerRepulState = false;
		bool Player2RepulState = false;

		// �ڐG�����I�u�W�F�N�g���e�v���C���[�ɃL���X�g�ł��Ă����甽����Ԃ��̃t���O���󂯎��
		if (ptrPlayer) PlayerRepulState = ptrPlayer->IsRepulState();
		if (ptrPlayer2) Player2RepulState = ptrPlayer2->IsRepulState();

		// �v���C���[�̂ǂ��炩��������Ԃœ����������ɃA�j���[�V�������s
		if (PlayerRepulState || Player2RepulState) {
			isBreak = true;
		}
	}

}
