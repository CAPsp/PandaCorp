//
// “G‚Ìˆ—
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
	inline void findMystericObj(){ mCurrentFind = true; }
	inline bool isFinding(){ return mCurrentFind; }

private:
	StateMachine<Enemy>* mStateMachine = nullptr;
	int mCurrentGID = -1;
	char mDirection = DIRECTON_DOWN;
	bool mCurrentFind = false;		// Œ»İ‹ŠE“à‚É‰ö‚µ‚¢‚à‚Ì‚ğ‚Æ‚ç‚¦‚Ä‚¢‚é‚©
	GameObj* mVision;				// éŒ¾‡‚ÌŠÖŒWã‚±‚±EnemyVision‚ğ‘‚¯‚È‚¢‚Ì‚ÅGameObj‚Å‘ã—p

};


// “G‚Ì‹ŠE”»’è‚ğ‚ÂGameObj
class EnemyVision : public GameObj{

public:
	EnemyVision(GameObjContainer*, Enemy*);
	virtual ~EnemyVision(){}
	virtual void update();
	virtual void draw();
	virtual void hit(GameObj*);

private:
	Enemy* mEnemy;

};