//
// 入力を管理する
//

#pragma once


// シングルトンパターン
class InputManager{

private:
	InputManager() = default;
	~InputManager() = default;

public:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static InputManager& getInstance(){
		static InputManager obj;
		return obj;
	}

public:
	void update();
	int checkPushFrame(int);

private:
	char key_type_state[256] = {0};	//各キーボードの状態
	int key_type_count[256] = {0};	//各キーボードが押されている時間


};