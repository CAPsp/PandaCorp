//
// �~���b�̎��Ԍv���Ɏg����N���X
//

#pragma once

#include <chrono>


class MSecTimer{

public:
	MSecTimer(){ start(); }
	
	// �^�C�}�[���X�^�[�g������
	void start(){
		mStartTime = std::chrono::system_clock::now();
	}

	// start()��ǂ񂾎�����o�߂����~���b��Ԃ�
	// �� long long�̌v���l��int�ɖ������L���X�g���Ă��邽�ߒ���
	int getCurrentTime(){
		auto time = std::chrono::system_clock::now() - mStartTime;
		return (int)(std::chrono::duration_cast< std::chrono::milliseconds>(time).count());
	}

private:
	std::chrono::system_clock::time_point mStartTime;

};