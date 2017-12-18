//
// ìGÇÃèàóù
//

#pragma once


#include "GameObj.h"
#include "StateMachine.h"


class Enemy : public GameObj{

public:
	Enemy(GameObjContainer*, Vec2D<int>);
	virtual ~Enemy();
	virtual void update();
	virtual void draw();
	virtual void hit(GameObj*);

	inline StateMachine<Enemy>* getStateMachine(){ return mStateMachine; }
	inline void changeGraphic(int id){
		if(id != -1){ mCurrentGID = id; }
	}
	inline char checkDirection(){ return mDirection; }
	inline void changeDirection(char dir){ mDirection = dir; }

private:
	StateMachine<Enemy>* mStateMachine = nullptr;
	int mCurrentGID = -1;
	char mDirection = DIRECTON_DOWN;

};