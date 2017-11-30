//
// UIのボタン
//

#pragma once


#include "Vec2DUtils.h"
#include <string>


class Button{

public:
	Button(Vec2D<int>, Vec2D<int>, std::string);
	void draw();
	bool update();	// 毎フレーム呼び出す必要がある

private:
	Vec2D<int> mC1, mC2;
	bool mBeforeFramePress = false;
	std::string mName;

};