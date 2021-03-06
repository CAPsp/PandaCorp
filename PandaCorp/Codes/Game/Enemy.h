//
// 敵の処理
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
	Vec2D<int> nextPatrolPoint();	// 次に向かう巡回先を返す

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
	bool mCurrentFind = false;				// 現在視界内に怪しいものをとらえているか
	std::vector<Vec2D<int>> mPatrolPoint;	// 巡回する座標を保持
	int mNextPatrolPointElem = 0;

};


// 敵の視界判定を持つGameObj
class EnemyVision : public GameObj{

public:
	EnemyVision(GameObjContainer*, Enemy*);
	virtual ~EnemyVision(){}
	virtual void update();
	virtual void draw();
	virtual void hit(GameObj*);

private:
	Enemy* mEnemy;
	Vec2D<int> mFindObjTmp;		// 視界あたり判定処理で一時的に使われる
	bool mIsPlayerFind = false;

};