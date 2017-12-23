//
// アイテム情報を格納するクラス
//

#pragma once


#include "GameObj.h"


class Item : public GameObj{

public:
	Item(GameObjContainer*, Vec2D<int>, int);
	virtual ~Item() = default;
	virtual void update(){}					// update関数による更新処理がない
	virtual void hit(GameObj*){}
	virtual void draw();					// 再描画時に呼び出す
	bool use();								// アイテムを使った場合の動作

	inline int checkGID(){ return mGraphID; }

private:
	int mGraphID;

};