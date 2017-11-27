#pragma once


#include "BaseScene.h"


class GameScene : public BaseScene{

public:
	GameScene(int num):mStageNum(num){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();

private:
	int mStageNum;

};