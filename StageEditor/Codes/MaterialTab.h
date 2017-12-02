//
// ステージにおけるマスを表示するタブ
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"
#include "MassData.h"


class MaterialTab{

public:
	MaterialTab();
	~MaterialTab(){}
	void clickDetectAndAction();		// クリックされたときの処理
	void draw();
	inline const MassData getMassData(){ return mSelectData; }

private:
	std::vector<int> mMassGraphID;
	MassData mSelectData;
	Vec2D<int> mOrigin;		// 左杖描画位置となる場所
	Vec2D<int> mMassNum;	// このタブ上に何個のマスが置けるか

};