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
	int checkPushFrame(int);						// キーの押されているフレーム数を返す
	bool existCursorInArea(int, int, int, int);		// 引数に渡されたエリアにマウスカーソルが存在するか
	inline bool isPushMouseLeft()	{ return mPushMouseL; }
	inline bool isPushMouseRight()	{ return mPushMouseR; }
	inline bool isUpMouseLeft()		{ return mUpMouseL; }
	inline bool isUpMouseRight()	{ return mUpMouseR; }

private:
	int mKeyFrame[256] = {0};	// 各キーボードが押されている時間
	int mMouseX, mMouseY;
	bool mPushMouseL, mPushMouseR;
	bool mUpMouseL, mUpMouseR;

};