#pragma once


#include "GameObj.h"


class Player : public GameObj{

public:
	Player(int, int);	// 引数は初期座標
	virtual ~Player();
	virtual void update();
	virtual void draw(int);
	virtual void hit(GameObj*);

private:
	Vec2D<double> mVel;	// 現在の速度

};