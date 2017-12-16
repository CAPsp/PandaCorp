#include "InputManager.h"

#include "DxLib.h"
#include "DebugMsgData.h"


void InputManager::update() {
	int i;

	GetHitKeyStateAll(key_type_state);

	for (i = 0; i < 256; i++) {
		if (key_type_state[i] == TRUE) {
			key_type_time[i]++;
		}
		else {
			key_type_time[i] = 0;
		}
	}

	// --- ko-tin�N�̍��Ƃ����̈��i �O�ցO�j ---
static int cnt[256]={0}:
for(j=0;j<256;j++){
	if(cnt[j]>=20){
		cnt[j]=0;
		key_type_count[j]=0;
	}
	if(key_type_state[i] == TRUE){
	if(cnt[j]<20){
	key_type_count[j]++;
	cnt[j]=0;
}
}
else{
	cnt[j]++;
}
}

	// ------

	// debug�p
	DebugMsgData::getInstance().setMsg("key_left"	, "Left: " + std::to_string(checkPushFrame(KEY_INPUT_LEFT)));
	DebugMsgData::getInstance().setMsg("key_right"	, "Right: " + std::to_string(checkPushFrame(KEY_INPUT_RIGHT)));
	DebugMsgData::getInstance().setMsg("key_down"	, "Down: " + std::to_string(checkPushFrame(KEY_INPUT_DOWN)));
	DebugMsgData::getInstance().setMsg("key_up"		, "Up: " + std::to_string(checkPushFrame(KEY_INPUT_UP)));

}


int InputManager::checkPushFrame(int key_code) {

	return key_type_time[key_code];

}


int InputManager::checkCount(int key_code) {

	return key_type_count[key_code];
}
