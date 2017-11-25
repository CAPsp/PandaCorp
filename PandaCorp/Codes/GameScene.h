#pragma once


#include "BaseScene.h"


class GameScene : public BaseScene{

public:
	GameScene(int){}
	virtual ~GameScene() = default;
	virtual scene_sig update(){ 
		scene_sig tmp;
		return tmp;
	}
	virtual bool begin(){ return true; }
	virtual bool end(){ return true; }

};