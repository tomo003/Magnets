/*!
@file MagnetsArea.h
@brief ���C�G���A
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MagnetArea : public GameObject
	{
		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)

		wstring m_texKey;
		Vec3 m_pos;
		float m_radius;

	public:

		MagnetArea(const std::shared_ptr<Stage>& stage, const Vec3& pos, const float& radius, const wstring& tex) :
			GameObject(stage),
			m_pos(pos),
			m_radius(radius),
			m_texKey(tex)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}
	};
}