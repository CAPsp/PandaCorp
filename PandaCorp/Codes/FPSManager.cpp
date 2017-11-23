#include "FPSManager.h"

#include "GlobalParam.h"
#include "DxLib.h"


// �^�C�}�[�̍X�V��1�t���[�����̑ҋ@����
void FPSManager::adjustment(){

	static int total_time = 0;

	// ����1�t���[���ł�����������(ms)
	int took_time = mTimer.getCurrentTime();

	// �ҋ@���Ȃ���΂Ȃ�Ȃ�����
	int wait_time = (1000 / GlobalParam::FPS) - took_time;
	if(wait_time > 0){
		WaitTimer(wait_time);
	}
	total_time += mTimer.getCurrentTime();

	// �t���[����1�i�߂鏈��
	mCurrentFrame++;
	if(total_time >= 1000){		// 1s �o������
		mFrameNumInSec	= mCurrentFrame;
		mCurrentFrame	= 0;
		total_time		= 0;
	}

	// ���̃t���[���ɂ����鎞�Ԃ��v������^�C�}�[���X�^�[�g
	mTimer.start();
}