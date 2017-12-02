//
// UI�̃{�^��
//

#pragma once


#include "Vec2DUtils.h"
#include <string>


class Button{

public:
	//Button():mName(""), mFont(-1){ sBtnCnt++; }
	~Button();
	Button(Vec2D<int>, Vec2D<int>, std::string);
	void draw();
	bool update();	// ���t���[���Ăяo���K�v������

private:
	Vec2D<int> mC1, mC2;
	bool mBeforeFramePress = false;
	std::string mName;
	int mFont;
	
	static int sBtnCnt;		// �g�p���Ă���{�^�������J�E���g

};