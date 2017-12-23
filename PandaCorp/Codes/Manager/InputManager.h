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
	int checkPushFrame(int);
	int checkCount(int);
	inline void activate(){ isActivated = true; }
	inline void deactivate(){ isActivated = false; }

private:
	char key_type_state[256]	= {0};	// �e�L�[�{�[�h�̏��
	int key_type_time[256]		= {0};	// �e�L�[�{�[�h��������Ă��鎞��
	int key_type_count[256]		= {0};	// �e�L�[�{�[�h�̘A�Ő�
	bool isActivated			= true; // ���͂����ݗL����
};
