/* !
@file BackGroundSprite.h
@brief �Q�[���X�e�[�W�̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class BackGroundSprite : public GameObject {
		shared_ptr<MeshResource> m_mesh;
		const Vec2 m_DefaultSize; // �����T�C�Y

	public:
		// �R���X�g���N�^
		BackGroundSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
		{
		}

		void OnCreate() override; 
	};

	//�摜���Ƃ̔w�i
	/*
	* @param scale		�\���T�C�Y
	* @param position	�\���ʒu
	* @param texKey		�g�p�e�N�X�`��
	*/
	class BackGroundSprite2 : public GameObject {
		
		Vec3 m_scale;
		Vec3 m_position;
		wstring m_texkey;

	public:
		BackGroundSprite2(const shared_ptr<Stage>& stage,
			const Vec3 scale,
			const Vec3 position,
			const wstring texkey
			) :
			GameObject(stage),
			m_scale(scale),
			m_position(position),
			m_texkey(texkey)
		{
		}

		void OnCreate() override; 
		void OnUpdate() override;
	};
}