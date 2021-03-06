#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"
#include "Enemy.h"
#include "Item.h"
#include "GraphManager.h"
#include "ItemInfoDef.h"
#include "ItemStock.h"



StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects, mHighScore);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
	}

	// ステージ外にでないためのあたり判定を作る
	Vec2D<int> fSize = {GameSceneParam::STAGE_FRAME_SIZE.x, GameSceneParam::STAGE_FRAME_SIZE.y};
	Vec2D<int> pos[4] = {	Vec2D<int>(fSize.x / 2, -10), Vec2D<int>(fSize.x / 2, fSize.y + 10),
							Vec2D<int>(-10, fSize.y / 2), Vec2D<int>(fSize.x + 10, fSize.y / 2)};
	Vec2D<int> size[4] = {	Vec2D<int>(fSize.x, 20), Vec2D<int>(fSize.x, 20),
							Vec2D<int>(20, fSize.y), Vec2D<int>(20, fSize.y)};
	for(int i = 0; i < 4; i++){
		Mass* tmp = new Mass(&(mObjects[1]), Vec2D<int>(0, 0), -1, Mass::mass_elem::NOT_PASS);
		tmp->changeHitAreaCenter(pos[i]);
		tmp->changeHitAreaSize(size[i]);
		mObjects[1].add(tmp);
	}

	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}

	// ステージ内に鍵がないときは持ち物に鍵を追加する
	bool flag = false;
	for(int i = 0; i < mObjects[1].checkSize(); i++){
		Item* tmp = dynamic_cast<Item*>(mObjects[1].checkElem(i));
		if(tmp != NULL &&
		   tmp->checkGID() == GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::KEY_POS)){

			flag = true;
			break;
		}
	}
	if(!flag){
		ItemStock::addItem(new Item(nullptr,
									Vec2D<int>(0, 0),
									GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::KEY_POS),
									true));
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
	
}


void StageControll::draw(){
	// レイヤー順に描画処理を行う
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}
}


// 現在の配置してるマスから触れたらクリアできるマスがあるかどうかを調査
void StageControll::checkExistClearMass(const ItemStock& itemStock){

	for(int i = 0; i < mObjects[1].checkSize(); i++){
		if(dynamic_cast<Mass*>(mObjects[1].checkElem(i)) != NULL){

			Mass tmp = *(dynamic_cast<Mass*>(mObjects[1].checkElem(i)));

			if(itemStock.checkClearCurrentStock(tmp)){
				(dynamic_cast<Mass*>(mObjects[1].checkElem(i)))->toClearMass();
			}
		}
	}

}