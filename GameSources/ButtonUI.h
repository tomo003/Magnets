/* !
@file ButtonUI.h
@brief �{�^���̎���
@author �����I
@detail�@UI�Ŏg���{�^���̎���
*/

#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ButtonSprite : public Sprites {
		const Vec2 m_DefaultSize;//�����T�C�Y

		bool m_changeSpeed; //�{�^���������ꂽ��_�ő��x�ύX�t���O

		Vec3 m_pos;
		wstring m_texkey;

	public:
		//�R���X�g���N�^
		ButtonSprite(const shared_ptr<Stage>& stage , const Vec3& pos,const wstring& texkey);
		//�f�X�g���N�^
		~ButtonSprite();

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;

	};

	class UiSprite : public Sprites {
		Vec2 m_size;
		Vec3 m_pos;
		wstring m_texkey;
		int m_layer;
	public:
		//�R���X�g���N�^
		UiSprite(const shared_ptr<Stage>& stage , const Vec2& size, const Vec3& pos,const wstring& texkey,const int& layer);
		//�f�X�g���N�^
		~UiSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}