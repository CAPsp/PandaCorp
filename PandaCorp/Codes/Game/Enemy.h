//
// �G�̏���
//

#pragma once


#include "GameObj.h"
#include "StateMachine.h"
#include <vector>
#include "Vec2DUtils.h"


class Enemy : public GameObj{

public:
	Enemy(GameObjContainer*, std::vector<Vec2D<int>>);
	virtual ~Enemy();
	virtual void update();
	virtual void draw();
	virtual void hit(GameObj*);
	Vec2D<int> nextPatrolPoint();	// ���Ɍ�����������Ԃ�

	inline StateMachine<Enemy>* getStateMachine(){ return mStateMachine; }
	inline void changeGraphic(int id){
		if(id != -1){ mCurrentGID = id; }
	}
	inline char checkDirection(){ return mDirection; }
	inline void changeDirection(char dir){ mDirection = dir; }
	inline void findMystericObj(){ mCurrentFind = true; }
	inline bool isFinding(){ return mCurrentFind; }

private:
	StateMachine<Enemy>* mStateMachine = nullptr;
	int mCurrentGID = -1;
	char mDirection = DIRECTON_DOWN;
	bool mCurrentFind = false;				// ���ݎ��E���ɉ��������̂��Ƃ炦�Ă��邩
	std::vector<Vec2D<int>> mPatrolPoint;	// ���񂷂���W��ێ�
	int mNextPatrolPointElem = 0;

};


// �G�̎��E���������GameObj
class EnemyVision : public GameObj{

public:
	EnemyVision(GameObjContainer*, Enemy*);
	virtual ~EnemyVision(){}
	virtual void update();
	virtual void draw();
	virtual void hit(GameObj*);

private:
	Enemy* mEnemy;
	Vec2D<int> mFindObjTmp;		// ���E�����蔻�菈���ňꎞ�I�Ɏg����
	bool mIsPlayerFind = false;

};