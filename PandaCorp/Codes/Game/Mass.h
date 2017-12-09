//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameObj.h"
#include <vector>


class Mass : public GameObj{

public:
	static const int LAYER_NUM = 4;		// マス画像３つ分とアイテム

public:
	Mass(int, int, std::vector<int>, bool);
	virtual ~Mass() = default;
	virtual void update(){}			// update関数による更新処理がない
	virtual void hit(GameObj&);
	void draw(int);					// 再描画時に呼び出す

private:
	std::vector<int> mGraphs;
	bool mPass;

};