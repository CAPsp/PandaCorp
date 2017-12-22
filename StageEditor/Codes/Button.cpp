#include "Button.h"

#include "DxLib.h"
#include "InputManager.h"
#include "Param.h"


int Button::sBtnCnt = 0;


Button::Button(){

	sBtnCnt++;
}

Button::Button(Vec2D<int> pos, Vec2D<int> size, std::string name):
	Button(){

	changePos(pos.x, pos.y);
	changeSize(size.x, size.y);
	changeName(name);
}


Button::~Button(){
	DeleteFontToHandle(mFont);
	sBtnCnt--;
}


void Button::draw(){

	// 押されてるときとそうでないときで色を変える
	if(mBeforeFramePress){
		DrawBox(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y, GetColor(155, 155, 155), true);
	}
	else{
		DrawBox(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y, GetColor(255, 255, 255), true);
	}

	DrawBox(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y, GetColor(0, 0, 0), false);	// 枠

	int width = GetDrawStringWidthToHandle(mName.c_str(), (int)(mName.size()), mFont);
	DrawStringToHandle(mPos.x + (mSize.x / 2) - (width / 2),
					   mPos.y + 2, 
					   mName.c_str(),
					   GetColor(0, 0, 0),
					   mFont);
	
}


bool Button::update(){

	bool isArea = InputManager::getInstance().existCursorInArea(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);
	bool isPush = InputManager::getInstance().isPushMouseLeft();

	// ボタンが押されたことを示す
	if(!isPush && isArea && mBeforeFramePress){
		mBeforeFramePress = isArea && isPush;
		return true;
	}

	// 次回フレームで押されていたかを扱うために保存
	mBeforeFramePress = isArea && isPush;

	return false;
}


void Button::changeSize(int x, int y){
	mSize.x = x;
	mSize.y = y;
	
	DeleteFontToHandle(mFont);
	mFont = CreateFontToHandle(("btn_" + std::to_string(sBtnCnt)).c_str(),
							   mSize.y - 5,
							   -1);
}