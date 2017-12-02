//
// ステージにおけるマスを表示するタブ
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"


class MaterialTab{

public:
	MaterialTab();
	~MaterialTab(){}
	void process();		// クリックされたときの処理
	void draw();

private:
	std::vector<int> mMassGraphID;
	int mSelectGraph = -1;
	Vec2D<int> mOrigin;		// 左杖描画位置となる場所
	Vec2D<int> mMassNum;	// このタブ上に何個のマスが置けるか

};