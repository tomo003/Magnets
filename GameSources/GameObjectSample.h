/*!
@file GameObjectSample.h
@brief CSV�t�@�C���ǂݍ��݊m�F�p���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�n�ʃI�u�W�F�N�g
	class GameObjectSample : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		GameObjectSample(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GameObjectSample();
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
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
		int m_State;
	public:
		MagnetN(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~MagnetN();
		virtual void OnCreate() override;
		virtual void OnUpdate();


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
		float m_MagAreaRadius = 3.0f;

		Vec3 m_Scale;
		Vec3 m_Position;
	public:
		MagnetS(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~MagnetS();
		virtual void OnCreate() override;
		virtual void OnUpdate();


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

	//�S�[���I�u�W�F�N�g
	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
		bool isDisplaySprite = false;
	public:
		Goal(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~Goal();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void PlayerGoal();
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;
	};

	//�Z�[�u�|�C���g
	class SavePoint : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		bool isCollPlayer = false;
		bool isCollPlayer2 = false;
	public:
		SavePoint(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~SavePoint();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void DeleteObject();
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};

	//�S�[���A���X�|�[���n�_�̏�̎l�p��
	class GoalSquareRed : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		GoalSquareRed(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareRed();
		virtual void OnCreate() override;
		void ChangeTexture();
	};

	//�S�[���A���X�|�[���n�_�̏�̎l�p��
	class GoalSquareBlue : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;

		std::vector<VertexPositionTexture> m_vertices; // ���_�f�[�^
		std::vector<uint16_t> m_indices; // ���_�C���f�b�N�X(���_�̕��я��E�g�ݍ��킹)
	public:
		GoalSquareBlue(const std::shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Position
		);
		virtual ~GoalSquareBlue();
		virtual void OnCreate() override;
		void ChangeTexture();
	};
}
//end basecross
