//
// Player�N���X�������X�e�[�g���`����
//

#pragma once

#include "State.h"
#include "Player.h"


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

};


// ����
class PlayerWalkState : public State<Player>{

public:
	PlayerWalkState() = default;
	virtual ~PlayerWalkState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};


// ������͂�ł���Ƃ�
class PlayerHoldState : public State<Player>{

public:
	PlayerHoldState() = default;
	virtual ~PlayerHoldState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};


// �A�C�e�����擾�����Ƃ�
class PlayerItemGetState : public State<Player>{

public:
	PlayerItemGetState() = default;
	virtual ~PlayerItemGetState() = default;
	virtual void Enter(Player*);
	virtual void Execute(Player*);
	virtual void Exit(Player*);

};
