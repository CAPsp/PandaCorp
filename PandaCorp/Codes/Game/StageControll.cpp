#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "GraphManager.h"


StageControll::StageControll(){
	
	mMass.resize(GameSceneParam::MASS_NUM.y);
	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		mMass[y].resize(GameSceneParam::MASS_NUM.x);
	}
	
}


StageControll::~StageControll(){}


void StageControll::draw(){

	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		for(int x = 0; x < GameSceneParam::MASS_NUM.x; x++){
			
			int id = GraphManager::getInstance().checkID("banana.png");

			DrawGraph(x * GameSceneParam::MASS_SIZE,
					  y * GameSceneParam::MASS_SIZE,
					  id,
					  true);
		}
	}

}