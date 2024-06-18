/* !
@file ShutterSprite.h
@brief �^�C�g���V�[���̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ShutterSprite : public Sprites {
		Vec2 m_DefaultSize; // �����T�C�Y
		Vec3 m_Pos;
		wstring m_textureKey;
		shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
	public:
		// �R���X�g���N�^
		ShutterSprite(const shared_ptr<Stage>& stage,Vec3& Pos,wstring );
		// �f�X�g���N�^
		~ShutterSprite();

		// ������
		virtual void OnCreate() override
		{
			m_ptrTrans = GetComponent<Transform>();
			Sprites::CreateSprite(m_Pos, m_DefaultSize, m_textureKey);
		}

		// �X�V����
		virtual void OnUpdate() override
		{

			Sprites::OnUpdate();
		}

		void SetPosition(const Vec3& position)
		{
			m_ptrTrans->SetPosition(position);
			m_Pos = position;
		}

		Vec3 GetPosition() const
		{
			return m_Pos;
		}
	};
}