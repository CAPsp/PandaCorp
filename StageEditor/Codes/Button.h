//
// UIのボタン
//

#pragma once


#include "Vec2DUtils.h"
#include <string>


class Button{

public:
	Button();
	Button(Vec2D<int>, Vec2D<int>, std::string);
	~Button();
	void draw();
	bool update();	// 毎フレーム呼び出す必要がある
	
	inline void changeName(std::string name){ mName = name; }
	inline void changePos(int x, int y){ mPos.x = x; mPos.y = y; }
	void changeSize(int, int);

private:
	Vec2D<int> mPos, mSize;
	bool mBeforeFramePress = false;
	std::string mName;
	int mFont;
	
	static int sBtnCnt;		// 使用しているボタン数をカウント

};