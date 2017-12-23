#include "Item.h"

#include "GameSceneParam.h"
#include "DxLib.h"



Item::Item(GameObjContainer* ow, Vec2D<int> pos, int graph)
	:mGraphID(graph),
	GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}){}


void Item::draw(){
	DrawGraph(mPos.x, mPos.y, mGraphID, true);
}


// trueを返すと仕様されてストックから削除される
bool Item::use(){

	return true;
}