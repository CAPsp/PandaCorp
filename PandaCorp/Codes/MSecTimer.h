//
// ミリ秒の時間計測に使われるクラス
//

#pragma once

#include <chrono>


class MSecTimer{

public:
	MSecTimer(){ start(); }
	
	// タイマーをスタートさせる
	void start(){
		mStartTime = std::chrono::system_clock::now();
	}

	// start()を読んだ時から経過したミリ秒を返す
	// ※ long longの計測値をintに無理やりキャストしているため注意
	int getCurrentTime(){
		auto time = std::chrono::system_clock::now() - mStartTime;
		return (int)(std::chrono::duration_cast< std::chrono::milliseconds>(time).count());
	}

private:
	std::chrono::system_clock::time_point mStartTime;

};