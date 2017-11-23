//
// �Q�[���S�̂��Ǘ����Ă���
// ���C�����[�v���񂵂Ă���̂�����
//

#pragma once


// �V���O���g���p�^�[��
class MainControll{

private:
	MainControll() = default;
	~MainControll() = default;

public:
	MainControll(const MainControll&) = delete;
	MainControll& operator=(const MainControll&) = delete;
	MainControll(MainControll&&) = delete;
	MainControll& operator=(MainControll&&) = delete;

	static MainControll& getInstance(){
		static MainControll obj;
		return obj;
	}

public:
	void doMainLoop();	// ���C�����[�v

private:
	unsigned int mFPS = 0;	// �v������FPS�l������

};