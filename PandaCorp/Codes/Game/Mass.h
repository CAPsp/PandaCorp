//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameObj.h"


class Mass : public GameObj{

public:
	static const int LAYER_NUM = 4;		// マス画像３つ分とアイテム

public:
	Mass(GameObjContainer*, Vec2D<int>, std::vector<int>, bool);
	virtual ~Mass() = default;
	virtual void update(){}			// update関数による更新処理がない
	virtual void hit(GameObj*);
	void draw(int);					// 再描画時に呼び出す

public:
	inline bool isPass(){ return mPass; }

private:
	std::vector<int> mGraphs;
	bool mPass;

};