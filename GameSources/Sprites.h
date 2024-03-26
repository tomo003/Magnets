/*!
@file Sprites.h
@brief �X�v���C�g�̐e�N���X�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		Vec2 m_spriteSize;	// �傫��
		Vec2 m_afterSize;	// �T�C�Y�ύX��̑傫��
		Vec3 m_position;	// UI�̈ʒu

		float m_uiSizeCoefficient;	// UI�T�C�Y�̌W��
		float m_totalTime;			// ����
		float m_waitSecond;			// �T�C�Y�ω��܂ł̑ҋ@����

		float m_alphaNum;	// �����x
		float m_fadeSpeed;	// �t�F�[�h�̑��x

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	protected:
		enum class SpriteType {
			Normal,			// �ʏ�
			ChangeColor,	// �F���ς��
			SeekSize,		// �T�C�Y���ς��
			Fade			// �t�F�[�h����
		};

		enum class FadeType {
			None,		// �������Ȃ�
			FadeOut,	// �t�F�[�h�A�E�g
			FadeIn		// �t�F�[�h�C��
		};

		enum class SeekSizeState {
			Wait,		// �ҋ@
			Stop,		// �I��
			SizeChange	// ���s
		};
		enum class SeekType {
			UpperLeft,	// ����
			UpperRight,	// �E��
			GameSprite,	// �E���ɓ����Ȃ���k��
			BottomLeft,	// �����
			BottomRight	// �E���
		};

		enum class ChangeColorState {
			DefaultSpeed,	// �ʏ푬�x
			SpeedChange		// ���x�ύX
		};

		enum SpriteType m_spriteType;			// �X�v���C�g�^�C�v
		enum FadeType m_fadeType;				// �t�F�[�h�^�C�v
		enum SeekSizeState m_isSeekSizeState;	// �T�C�Y�ύX�̏��
		enum SeekType m_seekType;				// �ω��������
		enum ChangeColorState m_isChangeColorState; // �F�ύX�̏��

	public:
		// �R���X�g���N�^
		Sprites(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~Sprites();


		/**
		* @brief �X�v���C�g���쐬����֐�
		*
		* @param position	�\���ʒu
		* @param size		�\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		*/
		void CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* @brief �t�F�[�h����X�v���C�g���쐬����֐�
		*
		* @param position	�\���ʒu
		* @param size		�\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		* @param fadeType	�t�F�[�h�^�C�v
		*/
		void CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType);

		/**
		* @brief �X�v���C�g�̓_�ŏ���
		*
		* @param flashSpeed �_�ł��鑬�x(1�Ńf�t�H���g�̃X�s�[�h(��b�Ɉ��_��))
		*/
		void UpdateFlashingSprite(int flashSpeed);

		/**
		* @brief �X�v���C�g�̓_�ŏ���
		*
		* @param flashSpeed ���i�̑��x(1�Ńf�t�H���g�̃X�s�[�h(��b�Ɉ��_��))
		* @param afterFlashSpeed �X�s�[�h�ύX��̑��x
		* @param speedChangeTrigger false:�ʏ푬�x true:�X�s�[�h�ύX�㑬�x
		*/
		void UpdateFlashingSprite(int flashSpeed, int afterFlashSpeed, bool speedChangeTrigger);

		/**
		* @brief �X�v���C�g�̃T�C�Y��ω������鏈��
		*
		* @param afterSize �ω���̃T�C�Y
		* @param seekSecond �ω��ɂ����鎞��
		* @param seekType �ω��^�C�v
		*/
		void UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType);

		/**
		* @brief �X�v���C�g�̃T�C�Y��ω������鏈��
		*
		* @param afterSize �ω���̃T�C�Y
		* @param seekSecond �ω��ɂ����鎞��
		* @param seekType �ω��^�C�v
		* @param waitSecond �ω��܂ł̎���
		*/
		void UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType, float waitSecond);

		/**
		* @brief �X�v���C�g���t�F�[�h�����鏈��
		*
		* @param fadeSecond �t�F�[�h�ɂ����鎞��
		*/
		void UpdateFadeSprite(float fadeSecond);

		// �T�C�Y�ύX�̏�Ԃ�ݒ肷��֐�
		void SetSeekSizeState(int state)
		{
			m_isSeekSizeState = (SeekSizeState)state;
		}

	};
}