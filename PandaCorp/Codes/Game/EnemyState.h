//
// Enemyクラスが扱うステートを定義する
//

#pragma once

#include "State.h"
#include "Enemy.h"
#include <map>
#include "GameTimer.h"
#include "GlobalParam.h"


// 常に更新する処理
class EnemyGlobalState : public State<Enemy>{

public:
	EnemyGlobalState() = default;
	virtual ~EnemyGlobalState() = default;
	virtual void Enter(Enemy*){}
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*){}

};


// 巡回
class EnemySearchState : public State<Enemy>{

public:
	EnemySearchState() = default;
	virtual ~EnemySearchState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

private:
	const std::string GRAPH_NAME = "stand_";
	std::map<char, std::vector<int>> mKeepGraph;
	int mAnimFrame = 0;

};


// 警戒(グラフィックは棒立ち)
class EnemyCautionState : public State<Enemy>{

public:
	EnemyCautionState() = default;
	virtual ~EnemyCautionState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

private:
	const std::string GRAPH_NAME = "stand_";
	const int DELAY_FRAME = GlobalParam::FPS / 2;		// 最初のこのフレーム分は怪しい動きをみてもガメオベラにならない
	const int CAUTION_FRAME = GlobalParam::FPS * 4;	// このフレーム中に怪しいうごきをみたらガメオベラ。このフレームが終了したらステートが変わる

	int mKeepGraph;
	GameTimer mTimer = GameTimer(0);
	bool mDelayFinished = false;

};


// 無力化
class EnemyDownState : public State<Enemy>{

public:
	EnemyDownState() = default;
	virtual ~EnemyDownState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

};


// 発見
class EnemyFindState : public State<Enemy>{

public:
	EnemyFindState() = default;
	virtual ~EnemyFindState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

private:
	const std::string GRAPH_NAME = "stand_";
	int mKeepGraph;
	GameTimer mDelayTimer = GameTimer(GlobalParam::FPS);	// 見つかった後の猶予フレーム

};
