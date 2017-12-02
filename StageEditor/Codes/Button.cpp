#include "Button.h"

#include "DxLib.h"
#include "InputManager.h"
#include "Param.h"


int Button::sBtnCnt = 0;


Button::Button(Vec2D<int> c1, Vec2D<int> c2, std::string name):
	mC1(c1), mC2(c2), mName(name){

	mFont = CreateFontToHandle(("btn_" + std::to_string(sBtnCnt)).c_str(),
							   c2.y - c1.y,
							   -1);
	
	sBtnCnt++;
}


Button::~Button(){
	DeleteFontToHandle(mFont);
	sBtnCnt--;
}


void Button::draw(){

	// 押されてるときとそうでないときで色を変える
	if(mBeforeFramePress){
		DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(155, 155, 155), true);
	}
	else{
		DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(255, 255, 255), true);
	}

	DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(0, 0, 0), false);	// 枠

	int width = GetDrawStringWidthToHandle(mName.c_str(), (int)(mName.size()), mFont);
	DrawStringToHandle((mC2.x + mC1.x) / 2 - width / 2,
					   mC1.y + 2, 
					   mName.c_str(),
					   GetColor(0, 0, 0),
					   mFont);
	
}


bool Button::update(){

	bool isArea = InputManager::getInstance().existCursorInArea(mC1.x, mC1.y, mC2.x, mC2.y);
	bool isPush = InputManager::getInstance().isPushedMouseLeft();

	// ボタンが押されたことを示す
	if(!isPush && isArea && mBeforeFramePress){
		mBeforeFramePress = isArea && isPush;
		return true;
	}

	// 次回フレームで押されていたかを扱うために保存
	mBeforeFramePress = isArea && isPush;

	return false;
}