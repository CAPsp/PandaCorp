//
// Player�N���X�������X�e�[�g���`����
//

#pragma once

#include "State.h"
#include "Player.h"
#include <string>
#include <vector>
#include <map>


// ��ɍX�V���鏈��
class PlayerGlobalState : public State<Player>{

public:
	PlayerGlobalState() = default;
	virtual ~PlayerGlobalState() = default;
	virtual void Enter(Player*){}
	virtual void Execute(Player*);
	virtual void Exit(Player*){}

};


// �ҋ@
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


// ����
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


// ������͂�ł���Ƃ�
class PlayerHoldState : public State<Player>{

public:
	PlayerHoldState() = default;
	virtual ~PlayerHoldState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	const std::string GRAPH_NAME = "hold_";

};


// �A�C�e�����擾�����Ƃ�
class PlayerItemGetState : public State<Player>{

public:
	PlayerItemGetState() = default;
	virtual ~PlayerItemGetState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

private:
	const std::string GRAPH_NAME = "item_get";

};
