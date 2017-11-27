#include "GameScene.h"


bool GameScene::begin(){
	return true;
}


scene_sig GameScene::update(){
	scene_sig rtn;



	rtn.next = scene_id::NONE;
	return rtn;
}


bool GameScene::end(){
	return true;
}