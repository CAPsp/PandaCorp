#pragma once


#include "GameObj.h"
#include "StateMachine.h"


class Player : public GameObj{

public:
	Player(GameObjContainer*, Vec2D<int>);
	virtual ~Player();
	virtual void update();
	virtual void draw(int);
	virtual void hit(GameObj*);
	void genHitBox();			// PlayerGenHitBoxオブジェクトの生成
	
	inline void addVelocity(Vec2D<double> v){ mVel += v; }
	inline Vec2D<double> checkVelocity(){ return mVel; }
	inline StateMachine<Player>* getStateMachine(){ return mStateMachine; }
	inline void changeGraphic(int id){
		if(id != -1){ mCurrentGID = id; }
	}
	inline char checkDirection(){ return mDirection; }
	inline void changeDirection(char dir){ mDirection = dir; }

private:
	Vec2D<double> mVel;	// 現在の速度
	StateMachine<Player>* mStateMachine = nullptr;
	int mCurrentGID = -1;
	char mDirection = DIRECTON_DOWN;

};