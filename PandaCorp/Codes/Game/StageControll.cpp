#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mMasses);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
	}

	mObjects.push_back(new Player(100, 100));
}


StageControll::~StageControll(){}


void StageControll::update(){

	// 1フレーム毎の更新処理
	for(auto mass : mMasses){ mass->update();	}
	for(auto obj : mObjects){ obj->update();	}

	// あたり判定処理
	for(auto obj : mObjects){

		// マスとのあたり判定
		for(auto mass : mMasses){

			if(obj->checkCollide(mass)){
				obj->hit(mass);
				mass->hit(obj);
			}
		}

		// 他オブジェクトとのあたり判定
		for(auto other : mObjects){
			if(other == obj){ continue; }

			if(obj->checkCollide(other)){
				obj->hit(other);
				other->hit(obj);
			}
		}

	}

	// マスはレイヤー順に描画処理を行う
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		for(auto mass : mMasses){
			mass->draw(i);
		}
	}
	for(auto obj : mObjects){
		obj->draw(0);
	}

}
