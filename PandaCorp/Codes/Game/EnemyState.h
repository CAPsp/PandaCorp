//
// Enemy�N���X�������X�e�[�g���`����
//

#pragma once

#include "State.h"
#include "Enemy.h"
#include <map>


// ��ɍX�V���鏈��
class EnemyGlobalState : public State<Enemy>{

public:
	EnemyGlobalState() = default;
	virtual ~EnemyGlobalState() = default;
	virtual void Enter(Enemy*){}
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*){}

};


// ����
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


// �x��
class EnemyCautionState : public State<Enemy>{

public:
	EnemyCautionState() = default;
	virtual ~EnemyCautionState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

};


// ���͉�
class EnemyDownState : public State<Enemy>{

public:
	EnemyDownState() = default;
	virtual ~EnemyDownState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

};


// ����
class EnemyFindState : public State<Enemy>{

public:
	EnemyFindState() = default;
	virtual ~EnemyFindState() = default;
	virtual void Enter(Enemy*);
	virtual void Execute(Enemy*);
	virtual void Exit(Enemy*);

};
