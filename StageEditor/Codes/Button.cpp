#include "Button.h"

#include "DxLib.h"
#include "InputManager.h"
#include "Param.h"



Button::Button(Vec2D<int> c1, Vec2D<int> c2, std::string name):
	mC1(c1), mC2(c2), mName(name){


}


void Button::draw(){

	// ������Ă�Ƃ��Ƃ����łȂ��Ƃ��ŐF��ς���
	if(mBeforeFramePress){
		DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(155, 155, 155), true);
	}
	else{
		DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(255, 255, 255), true);
	}

	DrawBox(mC1.x, mC1.y, mC2.x, mC2.y, GetColor(0, 0, 0), false);	// �g

	Vec2D<int> mid = { (mC2.x + mC1.x) / 2, (mC2.y + mC1.y) / 2 };
	int width = GetDrawStringWidth(mName.c_str(), (int)(strlen(mName.c_str())) );
	DrawString(mid.x - width / 2,
			   mid.y - Param::FONT_SIZE / 2,
			   mName.c_str(),
			   GetColor(0, 0, 0));
	
}


bool Button::update(){

	bool isArea = InputManager::getInstance().existCursorInArea(mC1.x, mC1.y, mC2.x, mC2.y);
	bool isPush = InputManager::getInstance().isPushedMouseLeft();

	// �{�^���������ꂽ���Ƃ�����
	if(!isPush && isArea && mBeforeFramePress){
		return true;
	}

	// ����t���[���ŉ�����Ă��������������߂ɕۑ�
	mBeforeFramePress = isArea && isPush;

	return false;
}