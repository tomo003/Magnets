/*!
@file GameObjectSample.h
@brief CSV�t�@�C���ǂݍ��݊m�F�p���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"
#include "MagnetArea.h"

namespace basecross {

	//�n�ʃI�u�W�F�N�g
	class GameObjectSample : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		GameObjectSample(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const wstring& Texture
		);
		virtual ~GameObjectSample();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//�e�N�X�`�����ύX�ł���l�p���I�u�W�F�N�g
	class ChangeTextureBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		wstring m_Texture;
	public:
		ChangeTextureBox(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const wstring& Texture
		);
		virtual ~ChangeTextureBox();
		virtual void OnCreate() override;
	};

	//N�ɂ̃I�u�W�F�N�g
	class MagnetN : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
		int m_State;
		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~MagnetN();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		//void OnDestroy()override;


		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
		//void EfkStop();
	};

	//S�ɂ̃I�u�W�F�N�g
	class MagnetS : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 4.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

		std::shared_ptr<EffectPlayer> m_efk;
		std::shared_ptr<MagnetArea> m_ptrArea;
	public:
		MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~MagnetS();
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		float GetMass() {
			return m_ObjMass;
		}
		float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		void ApplyForcePlayer();
		void ApplyForceSecondPlayer();

		void MoveMagnetArea(const Vec3 pos);
		//void EfkStop();
	};

	//�����̃I�u�W�F�N�g
	class Metal : public GameObject {
	public:
		enum class EState {
			eFalse = -1, // ��
			eN = 1, // �m��
			eS = 2, // �r��
			eMetal = 3 // ����
		};

	private:
		enum EState m_eMagPole;

		// �R���|�[�l���g�擾�ȗ��p
		std::shared_ptr<Transform> m_ptrTrans; // �g�����X�t�H�[���R���|�[�l���g
		std::shared_ptr<PNTStaticDraw> m_ptrDraw; // �h���[�R���|�[�l���g

		float m_ObjMass = 1.0f;
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;

	public:
		Metal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Metal();
		virtual void OnCreate() override;
		virtual void OnUpdate();
		//void OnDestroy()override;

		virtual int GetState() {
			return static_cast<int>(m_eMagPole);
		}
		virtual float GetMass() {
			return m_ObjMass;
		}
		virtual float GetAreaRadius() {
			return m_MagAreaRadius;
		}
		virtual Vec3 ABSV(const Vec3& v1, const Vec3& v2) {
			Vec3 VV = Vec3(fabsf(v1.x - v2.x), fabsf(v1.y - v2.y), fabsf(v1.z - v2.z));
			return VV;
		}

		virtual void ApplyForcePlayer();
		virtual void ApplyForceSecondPlayer();
	};

	//�X�^�[�g�I�u�W�F�N�g
	class Start : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		Start(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Start();
		virtual void OnCreate() override;
	};
}
//end basecross
