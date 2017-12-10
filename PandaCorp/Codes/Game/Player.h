#pragma once


#include "GameObj.h"
#include "StateMachine.h"


class Player : public GameObj{

public:
	Player(int, int);	// 引数は初期座標
	virtual ~Player();
	virtual void update();
	virtual void draw(int);
	virtual void hit(GameObj*);
	
	inline void addVelocity(Vec2D<double> v){ mVel += v; }
	inline Vec2D<double> checkVelocity(){ return mVel; }
	inline StateMachine<Player>* getStateMachine(){ return mStateMachine; }

private:
	Vec2D<double> mVel;	// 現在の速度
	StateMachine<Player>* mStateMachine = nullptr;

};