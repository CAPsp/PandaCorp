#pragma once



class GameTimer{

public:
	GameTimer(int);
	bool update();
	int getNowFrame();

private:
	int mFrame;
	int mFrameLimit;

};