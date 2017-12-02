#include "Stage.h"

#include "Param.h"
#include "InputManager.h"
#include "DxLib.h"


Stage::Stage(){
	mMass.resize(Param::MASS_NUM.y);
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		mMass[y].resize(Param::MASS_NUM.x);
		for(int x = 0; x < Param::MASS_NUM.x; x++){
			mMass[y][x].gID = -1;
			mMass[y][x].gPath = "";
		}
	}
}


Stage::Stage(std::string path){
	Stage();

}


void Stage::save(std::string path){

}


void Stage::draw(){

	for(int y = 0; y < mMass.size(); y++){
		for(int x = 0; x < mMass[y].size(); x++){
			DrawGraph(x * Param::MASS_SIZE, y * Param::MASS_SIZE, mMass[y][x].gID, false);
		}
	}

}


// マスがクリックされたときはログをとってtrueを返す
bool Stage::clickDetectAndAction(){

	if(InputManager::getInstance().isPushedMouseLeft()){

		for(int y = 0; y < mMass.size(); y++){
			for(int x = 0; x < mMass[y].size(); x++){

				Vec2D<int> c1 = {x * Param::MASS_SIZE,			y * Param::MASS_SIZE};
				Vec2D<int> c2 = {(x + 1) * Param::MASS_SIZE,	(y + 1) * Param::MASS_SIZE};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					mClickLog = {x, y};
					return true;
				}
			}
		}

	}

	return false;
}


void Stage::putDataToClickedTile(MassData data){
	mMass[mClickLog.y][mClickLog.x].gID = data.gID;
	mMass[mClickLog.y][mClickLog.x].gPath = data.gPath;
}