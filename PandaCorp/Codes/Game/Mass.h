//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameObj.h"


class Mass : public GameObj{

public:
	Mass(GameObjContainer*, Vec2D<int>, int, bool);
	virtual ~Mass() = default;
	virtual void update(){}			// update関数による更新処理がない
	virtual void hit(GameObj*);
	void draw();					// 再描画時に呼び出す

public:
	inline bool isPass(){ return mPass; }

private:
	int mGraph;
	bool mPass;

};