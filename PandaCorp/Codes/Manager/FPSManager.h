//
// FPS���Ǘ�����
//

#pragma once

#include "MSecTimer.h"


// �V���O���g���p�^�[��
class FPSManager{

private:
	FPSManager() = default;
	~FPSManager() = default;

public:
	FPSManager(const FPSManager&) = delete;
	FPSManager& operator=(const FPSManager&) = delete;
	FPSManager(FPSManager&&) = delete;
	FPSManager& operator=(FPSManager&&) = delete;

	static FPSManager& getInstance(){
		static FPSManager obj;
		return obj;
	}

public:
	inline unsigned int getCurrentFrame(){ return mCurrentFrame; }
	inline unsigned int getFrameNumInSec(){ return mFrameNumInSec; }
	void adjustment();	// ���C�����[�v�ł�����Ă΂Ȃ���΂Ȃ�Ȃ�

private:
	MSecTimer mTimer;
	unsigned int mCurrentFrame	= 0;	// �X�V���猻�݂܂ł̃t���[����
	unsigned int mFrameNumInSec	= 0;	// �O��1�b�Ԃŉ���̃t���[�����񂹂���

};