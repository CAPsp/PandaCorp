//
// ���͂��Ǘ�����
//

#pragma once


// �V���O���g���p�^�[��
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
	int checkPushFrame(int);						// �L�[�̉�����Ă���t���[������Ԃ�
	bool existCursorInArea(int, int, int, int);		// �����ɓn���ꂽ�G���A�Ƀ}�E�X�J�[�\�������݂��邩
	inline bool isPushedMouseLeft()		{ return mMouseL; }
	inline bool isPushedMouseRight()	{ return mMouseR; }


private:
	int mKeyFrame[256] = {0};	// �e�L�[�{�[�h��������Ă��鎞��
	int mMouseX, mMouseY;
	bool mMouseL, mMouseR;

};