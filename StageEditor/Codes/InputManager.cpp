#include "InputManager.h"

#include "DxLib.h"


void InputManager::update() {

	// キーボードの処理
	char key[256];
	GetHitKeyStateAll(key);

	for (int i = 0; i < 256; i++) {
		if (key[i] == TRUE) {
			mKeyFrame[i]++;
		}
		else {
			mKeyFrame[i] = 0;
		}
	}

	// マウスの処理
	GetMousePoint(&mMouseX, &mMouseY);

	int mouse = GetMouseInput();
	mUpMouseL = !(mouse & MOUSE_INPUT_LEFT) && mPushMouseL;
	mUpMouseR = !(mouse & MOUSE_INPUT_RIGHT) && mPushMouseR;
	mPushMouseL = (mouse & MOUSE_INPUT_LEFT)  ? true : false;
	mPushMouseR = (mouse & MOUSE_INPUT_RIGHT) ? true : false;

}


int InputManager::checkPushFrame(int key_code) {

	return mKeyFrame[key_code];

}


bool InputManager::existCursorInArea(int x1, int y1, int x2, int y2){

	return (x1 <= mMouseX && mMouseX <= x2 &&
			y1 <= mMouseY && mMouseY <= y2);

}