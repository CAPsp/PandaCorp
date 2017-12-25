#pragma once


#include "BaseScene.h"


class TitleScene : public BaseScene{

public:
	TitleScene() = default;
	virtual ~TitleScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();

private:
	void draw();

private:
	bool mIsSelectedStart = true;
	bool mIsEnded = false;
	int mFeedPal = 0;

};