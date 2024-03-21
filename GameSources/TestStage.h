/*!
@file TestStage.h
@brief 仮のステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class TestStage : public Stage {

	private:
		CsvFile m_GameStageTest;

	public:
		TestStage() :Stage()
		{}
	};
}
//end basecross
