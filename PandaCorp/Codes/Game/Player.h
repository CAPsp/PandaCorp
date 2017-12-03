//
// 動かすプレイヤーのクラス
//

#pragma once


#include "Character.h"


class Player : public Character{

public:
	Player();
	virtual ~Player();
	virtual void update();

private:
	int mAnimGID[4][4];

};