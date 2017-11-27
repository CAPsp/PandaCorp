#pragma once


#include "BaseScene.h"


class StageSelectScene : public BaseScene{

public:
	StageSelectScene() = default;
	virtual ~StageSelectScene() = default;
	virtual scene_sig update(){
		scene_sig tmp;
		return tmp;
	}
	virtual bool begin(){ return true; }
	virtual bool end(){ return true; }

};