#include "FPSManager.h"

#include "GlobalParam.h"
#include "DxLib.h"


// タイマーの更新と1フレーム毎の待機処理
void FPSManager::adjustment(){

	static int total_time = 0;

	// この1フレームでかかった時間(ms)
	int took_time = mTimer.getCurrentTime();

	// 待機しなければならない時間
	int wait_time = (1000 / GlobalParam::FPS) - took_time;
	if(wait_time > 0){
		WaitTimer(wait_time);
	}
	total_time += mTimer.getCurrentTime();

	// フレームを1進める処理
	mCurrentFrame++;
	if(total_time >= 1000){		// 1s 経ったら
		mFrameNumInSec	= mCurrentFrame;
		mCurrentFrame	= 0;
		total_time		= 0;
	}

	// 次のフレームにかかる時間を計測するタイマーをスタート
	mTimer.start();
}