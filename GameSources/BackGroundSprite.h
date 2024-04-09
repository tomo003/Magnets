/* !
@file BackGroundSprite.h
@brief �Q�[���X�e�[�W�̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class BackGroundSprite : public Sprites {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // �����T�C�Y

	public:
		// �R���X�g���N�^
		BackGroundSprite(const shared_ptr<Stage>& stage) :
			Sprites(stage),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; // ������
		void OnUpdate() override;
	};
}