#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"


const int lay = GameSceneParam::MASS_GRAPH_LAYER_NUM;


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
	}

	mObjects[lay].add(new Player(&mObjects[lay], Vec2D<int>(100, 100) ));

	for(int i = 0; i <= lay; i++){
		mObjects[i].update();
	}
}


StageControll::~StageControll(){}


void StageControll::update(){
	
	// 1フレーム毎の更新処理
	for(int i = 0; i <= lay; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->update();
		}
	}

	// レイヤー1以上のもの全てでオブジェクト同士のあたり判定を処理
	for(int i = 1; i < lay; i++){
		for(int j = i + 1; j <= lay; j++){

			for(int numI = 0; numI < mObjects[i].checkSize(); numI++){
				for(int numJ = 0; numJ < mObjects[j].checkSize(); numJ++){

					if( mObjects[i].checkElem(numI)->checkCollide( mObjects[j].checkElem(numJ) ) ){
						mObjects[i].checkElem(numI)->hit(mObjects[j].checkElem(numJ));
						mObjects[j].checkElem(numJ)->hit(mObjects[i].checkElem(numI));
					}
				}
			}

		}
	}

	// レイヤー順に描画処理を行う
	for(int i = 0; i <= lay; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}

	// コンテナの更新処理（追加、削除処理のために必須）
	for(int i = 0; i <= lay; i++){
		mObjects[i].update();
	}

}
