/* !
@file FlashSprite.h
@brief �_�ł���UI
*/
#pragma once
#include "stdafx.h"
#include "Flash.h"

namespace basecross {
	enum FlashType {
		Button,
		Icon
	};

	class FlashSprite : public Flash {
		Vec3 m_FsPosition;
		Vec2 m_defaultsize;//�����T�C�Y
		wstring m_texturekey;
		FlashType m_FlashType;

		bool m_changeSpeed; //�{�^���������ꂽ��_�ő��x�ύX�t���O
		//�g�[�^������
		float m_TotalTime;
		//�I������Ă��邩�ǂ���
		bool m_Selected;


	public:
		//�R���X�g���N�^
		FlashSprite(const shared_ptr<Stage>& stage, const Vec3& position, const Vec2& defaultsize, const wstring& TextureKey, const bool& selected);

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;

		void Delete();
		//�A�N�Z�T
		bool IsSelect() const {
			return m_Selected;
		}
		void SetSelect(bool b) {
			m_Selected = b;
		}

		FlashType GetFlashType() const {
			return m_FlashType;
		}

		void SetFlashType(const FlashType& flashType) {
			m_FlashType = flashType;
		}
	};
}

