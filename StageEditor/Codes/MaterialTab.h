//
// ステージにおける各要素を表示するタブ
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"
#include "GraphManager.h"


class MaterialTab{

public:
	MaterialTab(map_id);
	~MaterialTab(){}
	void clickDetectAndAction();		// クリックされたときの処理
	void draw();
	inline const int getMassData(){ return mSelectDataGID; }

private:
	std::vector<int> mMassGraphID;
	int mSelectDataGID;		// 選択中のマスグラフィックデータ
	Vec2D<int> mOrigin;		// 左杖描画位置となる場所
	Vec2D<int> mMassNum;	// このタブ上に何個のマスが置けるか

};