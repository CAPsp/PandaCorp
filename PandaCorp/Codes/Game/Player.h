#pragma once


#include "GameObj.h"


class Player : public GameObj{

public:
	Player(int, int);	// �����͏������W
	virtual ~Player();
	virtual void update();
	virtual void draw(int);
	virtual void hit(GameObj*);

private:
	Vec2D<double> mVel;	// ���݂̑��x

};