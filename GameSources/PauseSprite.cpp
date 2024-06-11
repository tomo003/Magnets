/*!
*
@file Arrow.h
@brief �X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�X�v���C�g
	//--------------------------------------------------------------------------------------
	PauseSprite::PauseSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, Col4 Color, float Alpha) :
		GameObject(StagePtr),
		m_textureKey(TextureKey),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_color(Color),
		m_alpha(Alpha)
	{}

	PauseSprite::~PauseSprite() {}
	void PauseSprite::OnCreate() {
		float helfSize = 0.5f;
		//����t����e�N�X�`���̒��_�̍��W�ƐF���w��
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), m_color, Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);//������
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);//��]�͂����Ȃ��ł��̂܂܃e�N�X�`�����g�p����̂�0.0f
		ptrTrans->SetPosition(m_startPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
		SetDrawLayer(10);//�\������D��x�i�������������D�悵�ĕ\�������j
	}

	void PauseSprite::OnUpdate() {
		float helfSize = 0.5f;
		//����t����e�N�X�`���̒��_�̍��W�ƐF���w��
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), m_color, Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);//������
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_alpha));
		auto PtrScene = App::GetApp()->GetScene<Scene>();

		if (PtrScene->GetGameState() == GameState::MainGame)
		{
			GetStage()->RemoveGameObject<PauseSprite>(GetThis<GameObject>());
		}

	}

	void PauseSprite::Flashing() {
		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		if (m_alpha <= 0.0f) {
			n = +1.0f;
		}
		if (m_alpha >= 1.0f) {
			n = -1.0f;
		}
		m_alpha += sin(n) * delta;
		ptrDraw->SetDiffuse(Col4(1.0, 1.0f, 1.0f, m_alpha));
	}

	void PauseSprite::Start()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		auto pos = ptrTrans->GetPosition();
		Vec3 dir = Vec3(-1.0f, 0.0f, 0.0f);
		if (pos.x >= 0.0f)
		{
			pos += dir * 1500 * delta;
		}
		else
		{
			m_totalTime += delta;
		}

		if (m_totalTime > 1.0f)
		{
			n = -1.0f;
			m_alpha += sin(n) * delta;
		}
		ptrTrans->SetPosition(pos);
		ptrDraw->SetDiffuse(Col4(1.0, 1.0f, 1.0f, m_alpha));
	}
}