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

	// マスはレイヤー順に描画処理を行う
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		for(auto mass : mMasses){
			mass.draw(i);
		}
	}
	for(auto obj : mObjects){
		obj->update();
	}

	// TODO: ゲーム内オブジェクト同士あたり判定処理

}
