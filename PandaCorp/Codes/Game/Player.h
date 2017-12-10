#pragma once


#include "GameObj.h"
#include "StateMachine.h"


class Player : public GameObj{

public:
	Player(int, int);	// �����͏������W
	virtual ~Player();
	virtual void update();
	virtual void draw(int);
	virtual void hit(GameObj*);
	
	inline void addVelocity(Vec2D<double> v){ mVel += v; }
	inline Vec2D<double> checkVelocity(){ return mVel; }
	inline StateMachine<Player>* getStateMachine(){ return mStateMachine; }

private:
	Vec2D<double> mVel;	// ���݂̑��x
	StateMachine<Player>* mStateMachine = nullptr;

};