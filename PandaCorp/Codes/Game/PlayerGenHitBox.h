//
// 決定キーなどを押したときにプレイヤー前方にあるものを識別するためのオブジェクト
//

#pragma once


#include "GameObj.h"
#include "Player.h"


class PlayerGenHitBox : public GameObj{

public:
	PlayerGenHitBox() = delete;
	PlayerGenHitBox(GameObjContainer*, Player*);
	virtual ~PlayerGenHitBox() = default;
	virtual void update();	// 1フレーム後に消滅する
	virtual void draw();
	virtual void hit(GameObj*);

private:
	Player* mPlayer;

};