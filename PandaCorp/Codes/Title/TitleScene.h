#pragma once


#include "BaseScene.h"


class TitleScene : public BaseScene{

public:
	TitleScene() = default;
	virtual ~TitleScene() = default;
	virtual scene_sig update(){
		scene_sig tmp;
		return tmp;
	}
	virtual bool begin(){ return true; }
	virtual bool end(){ return true; }

};