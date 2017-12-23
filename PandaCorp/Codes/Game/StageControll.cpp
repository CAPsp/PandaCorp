#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"
#include "Enemy.h"


//const int lay = GameSceneParam::MASS_GRAPH_LAYER_NUM;


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects, mHighScore);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
	}

	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}
}


StageControll::~StageControll(){}


void StageControll::update(){
	
	// 1フレーム毎の更新処理
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->update();
		}
	}

	// オブジェクト同士のあたり判定を処理	
	for(int i = 0; i < mObjects[1].checkSize(); i++){
		for(int j = 0; j < mObjects[1].checkSize(); j++){

			if(i == j && i == j){ continue; }

			// マス同士のあたり判定は考慮しない
			if( (dynamic_cast<Mass*>(mObjects[1].checkElem(i)) != NULL) &&
				(dynamic_cast<Mass*>(mObjects[1].checkElem(j)) != NULL) ){
				continue;
			}

			if( mObjects[1].checkElem(i)->checkCollide( mObjects[1].checkElem(j) ) ){
				mObjects[1].checkElem(i)->hit(mObjects[1].checkElem(j));
				mObjects[1].checkElem(j)->hit(mObjects[1].checkElem(i));
			}
		}
	}

	// コンテナの更新処理（追加、削除、描画順ソート処理のために必須）
	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}

	// レイヤー順に描画処理を行う
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}

}
