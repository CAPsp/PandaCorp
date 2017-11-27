#include "InputManager.h"

#include "DxLib.h"


void InputManager::update() {
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

int InputManager::checkPushFrame(int key_code) {

	return key_type_count[key_code];

}
