/*!
@file PlayerBanner.h
@brief �v���C���[�̃o�i�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBanner : public GameObject
	{
		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PTStaticDraw> m_DrawComp; // �h���[�R���|�[�l���g

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		Vec3 m_playerPos = Vec3(0);

		wstring m_texKey; // �e�N�X�`��

	public:

		PlayerBanner(const std::shared_ptr<Stage>& stage,const wstring& tex) :
			GameObject(stage),
			m_texKey(tex)
		{}

		void OnCreate() override;
	};
}