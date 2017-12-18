//
// Enemyクラスが扱うステートを定義する
//

#pragma once

#include "State.h"
#include "Enemy.h"
#include <map>


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


// 警戒
class EnemyCautionState : public State<Enemy>{

public:
	EnemyCautionState() = default;
	virtual ~EnemyCautionState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

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

};
