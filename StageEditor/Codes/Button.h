//
// UI�̃{�^��
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
	bool update();	// ���t���[���Ăяo���K�v������
	
	inline void changeName(std::string name){ mName = name; }
	inline void changePos(int x, int y){ mPos.x = x; mPos.y = y; }
	void changeSize(int, int);

private:
	Vec2D<int> mPos, mSize;
	bool mBeforeFramePress = false;
	std::string mName;
	int mFont;
	
	static int sBtnCnt;		// �g�p���Ă���{�^�������J�E���g

};