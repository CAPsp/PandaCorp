//
// FPSを管理する
//

#pragma once

#include "MSecTimer.h"


// シングルトンパターン
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
	void adjustment();	// メインループでこれを呼ばなければならない

private:
	MSecTimer mTimer;
	unsigned int mCurrentFrame	= 0;	// 更新から現在までのフレーム数
	unsigned int mFrameNumInSec	= 0;	// 前の1秒間で何回のフレームを回せたか

};