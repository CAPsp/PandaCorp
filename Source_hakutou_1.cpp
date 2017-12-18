#include "DxLib.h"

char key_type_state[256] = { 0 };	//各キーボードの状態
int key_type_count[256] = { 0 };	//各キーボードが押されている時間

void update();
int checkPushFrame(int);

void update() {
	int i;

	GetHitKeyStateAll(key_type_state);

	for (i = 0; i < 256; i++) {
		if (key_type_state[i] == TRUE) {
			key_type_count[i]++;
		}
		else {
			key_type_count[i] = 0;
		}
	}
}

int checkPushFrame(int key_code) {

	return key_type_count[key_code];

}
