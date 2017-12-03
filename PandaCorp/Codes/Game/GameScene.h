#pragma once


#include "BaseScene.h"
#include "StageControll.h"


class GameScene : public BaseScene{

public:
	GameScene(int num):mStageNum(num), mStage("Stage/test.json"){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();

private:
	int mStageNum;
	StageControll mStage;

};