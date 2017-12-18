#pragma once


#include "BaseScene.h"


class StageSelectScene : public BaseScene{

public:
	StageSelectScene() = default;
	virtual ~StageSelectScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();

};