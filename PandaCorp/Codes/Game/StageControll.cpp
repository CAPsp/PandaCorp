#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(&mMasses);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
	}

	mObjects.add(new Player(&mObjects, Vec2D<int>(100, 100) ));
}


StageControll::~StageControll(){}


void StageControll::update(){

	std::vector<GameObj*>& masses = mMasses.checkData();
	std::vector<GameObj*>& objs = mObjects.checkData();

	// 1フレーム毎の更新処理
	for(auto mass : masses){ mass->update();	}
	for(auto obj : objs){ obj->update();	}

	// あたり判定処理
	for(auto obj : objs){

		// マスとのあたり判定
		for(auto mass : masses){

			if(obj->checkCollide(mass)){
				obj->hit(mass);
				mass->hit(obj);
			}
		}

		// 他オブジェクトとのあたり判定
		for(auto other : objs){
			if(other == obj){ continue; }

			if(obj->checkCollide(other)){
				obj->hit(other);
				other->hit(obj);
			}
		}

	}

	// マスはレイヤー順に描画処理を行う
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		
		// レイヤー2より前に他ゲームオブジェクトは描画される
		if(i == 1){
			for(auto obj : objs){
				obj->draw(0);
			}
		}
		
		for(auto mass : masses){
			mass->draw(i);
		}
	}

	// GameObjを入れてあるコンテナの更新処理（追加、削除処理のために必須）
	mObjects.update();
	mMasses.update();

}
