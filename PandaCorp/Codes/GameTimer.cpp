#include "GameTimer.h"


GameTimer::GameTimer(int limit){
	mFrame = 0;
	mFrameLimit = limit;
}

bool GameTimer::update(){
	mFrame++;
	if(mFrame>mFrameLimit)return false;
	else return true;
}


int GameTimer::getNowFrame(){
	return mFrame;
}
