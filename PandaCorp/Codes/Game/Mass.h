//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameObj.h"
#include "Player.h"


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
	virtual void hit(GameObj*);
	void draw();					// 再描画時に呼び出す

public:
	inline mass_elem checkElem(){ return mElem; }
	inline bool isPass(){ return mElem == NORMAL; }
	inline bool isObstacle(){ return mElem == OBSTACLE; }
	//inline void setElem(mass_elem elem){ mElem = elem; }

private:
	int mGraph;
	mass_elem mElem;

};