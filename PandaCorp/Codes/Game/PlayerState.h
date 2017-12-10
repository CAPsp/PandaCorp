//
// Playerクラスが扱うステートを定義する
//

#pragma once

#include "State.h"
#include "Player.h"


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

};


// 歩き
class PlayerWalkState : public State<Player>{

public:
	PlayerWalkState() = default;
	virtual ~PlayerWalkState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};


// 何かを掴んでいるとき
class PlayerHoldState : public State<Player>{

public:
	PlayerHoldState() = default;
	virtual ~PlayerHoldState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};


// アイテムを取得したとき
class PlayerItemGetState : public State<Player>{

public:
	PlayerItemGetState() = default;
	virtual ~PlayerItemGetState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};
