/*!
@file StartMoveObject.h
@brief ゲームステージ開始時プレイヤーを運んでくるオブジェクト
@autor 吉田鈴
@detail ゲームステージ開始時プレイヤーを運んでくるオブジェクトや登場時のプレイヤーの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// ゲームステージ開始時プレイヤーを運んでくるオブジェクト
	//--------------------------------------------------------------------------------------
	class StartMoveObject : public GameObject{
		Vec3 m_Scale;
		Vec3 m_Position;

		shared_ptr<SoundItem> m_operationSound; // 稼働音を流すためのアイテム

		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjS; // ChangeTextureBlock(見せかけの磁石オブジェクト)
		std::shared_ptr<ChangeTextureBlock> m_ptrMagObjN; // ChangeTextureBlock(見せかけの磁石オブジェクト)

		std::shared_ptr<Player> m_ptrPlayer;   // Player
		std::shared_ptr<Player2> m_ptrPlayer2; // Player2

		bool leavePlayer = false;  // プレイヤーが磁石から離れているか
		bool leavePlayer2 = false; // プレイヤー2が磁石から離れているか

		bool OperationSEPlay = false; // 稼働音が流れているかの判定
		bool StopSEPlay = false;      // 音が止まっているかの判定

public:
	// 構築と破棄
	StartMoveObject::StartMoveObject(const std::shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	StartMoveObject::~StartMoveObject() {}
	// 初期化
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	};

}

