/*!
@file Sprites.cpp
@brief �摜�����̊�{�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_spriteSize(Vec2(0.0f)),
		m_afterSize(Vec2(0.0f)),
		m_position(Vec3(0.0f)),
		m_uiSizeCoefficient(0.0f),
		m_totalTime(0.0f),
		m_waitSecond(5.0f),
		m_alphaNum(0.0f),
		m_fadeSpeed(0.01f),
		m_spriteType(SpriteType::Normal),
		m_fadeType(FadeType::None),
		m_isSeekSizeState(SeekSizeState::Wait),
		m_seekType(SeekType::BottomRight),
		m_isChangeColorState(ChangeColorState::DefaultSpeed)
	{
	}
	// �f�X�g���N�^
	Sprites::~Sprites() {}

	void Sprites::CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey)
	{
		// �\���ʒu�ƕ\���T�C�Y�������o�ϐ��ɓ���Ă���
		m_position = position;
		m_spriteSize = size;

		// ���_�f�[�^�̐ݒ� //
		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);
		m_vertices = {
			{Vec3(0.0f	 , 0.0f	   , 0.0f), white, Vec2(0.0f, 0.0f)}, // ����
			{Vec3(size.x , 0.0f	   , 0.0f), white, Vec2(1.0f, 0.0f)}, // �E��
			{Vec3(0.0f	 , -size.y , 0.0f), white, Vec2(0.0f, 1.0f)}, // ����
			{Vec3(size.x , -size.y , 0.0f), white, Vec2(1.0f, 1.0f)}, // �E��
		};
		m_indices = {
			0, 1, 2,
			2, 1, 3
		};
		// �����܂� //

		// �����ڂ̐ݒ�
		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(texKey);

		// �ʒu�̐ݒ�
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
		// �`�惌�C���[���őO�ʂ�
		SetDrawLayer((int)DrawLayer::ForeFront);
	}

	void Sprites::CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType) {

		// �t�F�[�h�A�E�g���t�F�[�h�C�����擾
		m_fadeType = fadeType;

		// �t�F�[�h�C���Ȃ�
		if (m_fadeType == FadeType::FadeIn) {
			// �A���t�@�l��1��
			m_alphaNum = 1.0f;
		}
		else if (m_fadeType == FadeType::FadeOut) // �t�F�[�h�A�E�g�Ȃ�
		{
			// �A���t�@�l��0��
			m_alphaNum = 0.0f;
		}

		// �X�v���C�g�̍쐬
		CreateSprite(position, size, texKey);
	}

	void Sprites::UpdateFlashingSprite(int flashSpeed)
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime(); // ���Ԃ̎擾

		// �T�C���J�[�u���g���ē_�ł�\��
		float color = sinf(m_totalTime);
		// �l�����+�l�ɂ��鏈��
		if (color < 0.0f)
		{
			color *= -1;
		}

		// �ω����x�𔽉f(��葬�x)
		m_totalTime += delta * flashSpeed;

		// ���_�f�[�^�̍X�V
		auto drawComp = GetComponent<PCTSpriteDraw>();
		m_vertices[0].color = Col4(color, color, color, 1.0f);
		m_vertices[1].color = Col4(color, color, color, 1.0f);
		m_vertices[2].color = Col4(color, color, color, 1.0f);
		m_vertices[3].color = Col4(color, color, color, 1.0f);
		drawComp->UpdateVertices(m_vertices);
	}

	void Sprites::UpdateFlashingSprite(int flashSpeed, int afterFlashSpeed, bool speedChangeTrigger)
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// ���Ԃ̎擾

		// �T�C���J�[�u���g���ē_�ł�\��
		float color = sinf(m_totalTime);
		// �l�����+�l�ɂ��鏈��
		if (color < 0.0f)
		{
			color *= -1;
		}

		// �ʏ�̑��x�Ȃ�
		if (m_isChangeColorState == ChangeColorState::DefaultSpeed)
		{
			m_totalTime += delta * flashSpeed; // �ω����x�𔽉f

			// ���_�f�[�^�̍X�V
			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(color, color, color, 1.0f);
			m_vertices[1].color = Col4(color, color, color, 1.0f);
			m_vertices[2].color = Col4(color, color, color, 1.0f);
			m_vertices[3].color = Col4(color, color, color, 1.0f);
			drawComp->UpdateVertices(m_vertices);

			// �g���K�[��true�ɂȂ�����
			if (speedChangeTrigger)
			{
				// �X�s�[�h��ω�������
				m_isChangeColorState = ChangeColorState::SpeedChange;
			}
		}

		// �X�e�[�g���X�s�[�h�ω���ԂȂ�
		if (m_isChangeColorState == ChangeColorState::SpeedChange)
		{
			m_totalTime += delta * afterFlashSpeed; // �ω����x�𔽉f

			// ���_�f�[�^�̍X�V
			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(color, color, color, 1.0f);
			m_vertices[1].color = Col4(color, color, color, 1.0f);
			m_vertices[2].color = Col4(color, color, color, 1.0f);
			m_vertices[3].color = Col4(color, color, color, 1.0f);
			drawComp->UpdateVertices(m_vertices);

			// �g���K�[��false�ɂȂ�����
			if (!speedChangeTrigger)
			{
				// �X�s�[�h��߂�
				m_isChangeColorState = ChangeColorState::DefaultSpeed;
			}
		}
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType)
	{
		// �X�e�[�g����~��ԂłȂ����
		if (m_isSeekSizeState != SeekSizeState::Stop)
		{
			// �T�C�Y�ύX��ԂɂȂ�
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}

		// �T�C�Y�ύX��ԂȂ�
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			// ���Ԃ̎擾
			auto& app = App::GetApp();
			auto delta = app->GetElapsedTime();

			// �T�C�Y�W����ω�������
			m_uiSizeCoefficient += delta / seekSecond;

			// �ǂ̒��_����ɂ��邩
			switch (seekType)
			{
			case SeekType::UpperLeft: // ����
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::UpperRight: // �E��
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite: // 
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft: // ����
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight: // �E��
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				break;

			default: // ��O�Ȃ牽�����Ȃ�
				break;
			}

			// ���_�f�[�^�̍X�V
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(m_vertices);

			// �W����1���傫���Ȃ�����
			if (m_uiSizeCoefficient > 1.0f)
			{
				// �W����1�ɌŒ肷��
				m_uiSizeCoefficient = 1.0f;
			}

		}
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, float seekSecond, const SeekType& seekType, float waitSecond)
	{
		// ���Ԃ̎擾
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		// �ҋ@���ԗp
		m_totalTime += delta;

		// �ҋ@���Ԃ��I����Ă��邩�X�e�[�g����~��ԂłȂ����
		if (m_totalTime > waitSecond && m_isSeekSizeState != SeekSizeState::Stop)
		{
			// �T�C�Y�ύX��ԂɈڍs
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}

		// �T�C�Y�ύX��ԂȂ�
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			// �W����ω�
			m_uiSizeCoefficient += delta / seekSecond;

			// �ǂ̒��_����ɂ��邩
			switch (seekType)
			{
			case SeekType::UpperLeft: // ����
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft: // ����
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight: // �E��
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				break;

			default:
				break;
			}

			// ���_�f�[�^�̍X�V
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(m_vertices);

			// �W����1�ȏ�ɂȂ�����
			if (m_uiSizeCoefficient > 1.0f)
			{
				// ��~��ԂɂȂ�
				m_isSeekSizeState = SeekSizeState::Stop;
			}
		}
	}

	void Sprites::UpdateFadeSprite(float fadeSecond)
	{
		// ���Ԃ̎擾
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		// �t�F�[�h�^�C�v���t�F�[�h�C���Ȃ�
		if (m_fadeType == FadeType::FadeIn)
		{
			// �A���t�@�l������������
			m_alphaNum -= delta / fadeSecond;

			// �A���t�@�l�̔��f
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
		}

		// �t�F�[�h�^�C�v���t�F�[�h�A�E�g�Ȃ�
		if (m_fadeType == FadeType::FadeOut)
		{
			// �A���t�@�l������������
			m_alphaNum += delta / fadeSecond;

			// �A���t�@�l�̔��f
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
		}
	}
}