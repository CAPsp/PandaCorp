//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameObj.h"


class Mass : public GameObj{

public:
	enum mass_elem{
		NORMAL,
		NOT_PASS,
		OBSTACLE
	};

public:
	Mass(GameObjContainer*, Vec2D<int>, int, mass_elem = NORMAL);
	virtual ~Mass() = default;
	virtual void update(){}			// update関数による更新処理がない
	virtual void hit(GameObj*){}
	virtual void draw();

public:
	inline mass_elem checkElem(){ return mElem; }
	inline bool isPass()		{ return mElem == NORMAL; }
	inline bool isObstacle()	{ return mElem == OBSTACLE; }
	inline void toClearMass()	{ mIsClear = true; }
	inline bool isClear()		{ return mIsClear; }
	inline int checkGraphID()	{ return mGraph;}
	
private:
	int mGraph;
	mass_elem mElem;
	bool mIsClear = false;	// このマスに触れたらゲームをクリアできる

};