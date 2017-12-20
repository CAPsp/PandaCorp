#pragma once


#include "BaseScene.h"
#include "StageControll.h"
#include "StageEndProcess.h"


class GameScene : public BaseScene{

public:
	GameScene(int num) :mStageNum(num), mStage("Stage/test.json"){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();

// �X�e�[�W�I�����������Ƃ��ɌĂ΂��ÓI�֐��Q
public:
	static void toGameOver(){ sEndProcess.gameover(); }
	static void toClear(){ sEndProcess.clear(); }
	static void toStageSelect(){ sEndProcess.returnStageSelect(); }

private:
	int mStageNum;
	StageControll mStage;
	static StageEndProcess sEndProcess;

};