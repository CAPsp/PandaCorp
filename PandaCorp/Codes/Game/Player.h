#pragma once


#include "GameObj.h"


class Player : public GameObj{

public:
	Player(int, int);	// ˆø”‚Í‰ŠúÀ•W
	virtual ~Player();
	virtual void update();
	virtual void hit(GameObj&);


};