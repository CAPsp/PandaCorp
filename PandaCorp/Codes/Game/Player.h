#pragma once


#include "GameObj.h"


class Player : public GameObj{

public:
	Player(int, int);	// 引数は初期座標
	virtual ~Player();
	virtual void update();
	virtual void hit(GameObj&);


};