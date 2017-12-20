//
// ステージ終了時の処理を受け持つクラス
// 静的な扱いを受けることを考慮して設計
//

#pragma once


#include "BaseScene.h"


class StageEndProcess{

public:
	enum state{
		NON_ACTIVE,
		RETURN_SELECT,
		GAME_OVER,
		CLEAR
	};

public:
	StageEndProcess() = default;
	~StageEndProcess() = default;
	scene_sig update();
	inline void init(){ mCurrentState = NON_ACTIVE; }

	inline void gameover()			{ if(mCurrentState == NON_ACTIVE){ mCurrentState = GAME_OVER;		} }
	inline void clear()				{ if(mCurrentState == NON_ACTIVE){ mCurrentState = CLEAR;			} }
	inline void returnStageSelect()	{ if(mCurrentState == NON_ACTIVE){ mCurrentState = RETURN_SELECT;	} }

private:
	state mCurrentState;

};