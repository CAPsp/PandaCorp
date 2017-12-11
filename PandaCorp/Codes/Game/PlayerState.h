//
// Playerクラスが扱うステートを定義する
//

#pragma once

#include "State.h"
#include "Player.h"
#include <string>
#include <vector>
#include <map>
#include "Mass.h"


// 常に更新する処理
class PlayerGlobalState : public State<Player>{

public:
	PlayerGlobalState() = default;
	virtual ~PlayerGlobalState() = default;
	virtual void Enter(Player*){}
	virtual void Execute(Player*);
	virtual void Exit(Player*){}

};


// 待機
class PlayerStandState : public State<Player>{

public:
	PlayerStandState() = default;
	virtual ~PlayerStandState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	const std::string GRAPH_NAME = "stand_";
	std::map<char, std::vector<int>> mKeepGraph;
	int mAnimFrame = 0;

};


// 歩き
class PlayerWalkState : public State<Player>{

public:
	PlayerWalkState() = default;
	virtual ~PlayerWalkState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	const std::string GRAPH_NAME = "walk_";
	std::map<char, std::vector<int>> mKeepGraph;
	int mAnimFrame = 0;

};


// 何かを掴んでいるとき
class PlayerHoldState : public State<Player>{

public:
	PlayerHoldState(Mass* mass) :mMass(mass){}
	virtual ~PlayerHoldState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	void holdAction(Player*);

private:
	const std::string GRAPH_NAME = "hold_";
	Mass* mMass;
	std::vector<int> mKeepGraph;
	int mAnimFrame = 0;
	Vec2D<int> mPreviousPlayerPos;	// オブジェクトを動かす処理で必要

};


// アイテムを取得したとき
class PlayerItemGetState : public State<Player>{

public:
	PlayerItemGetState() = default;
	virtual ~PlayerItemGetState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	const std::string GRAPH_NAME = "item_get";
	std::vector<int> mKeepGraph;
	int mAnimFrame = 0;

};
