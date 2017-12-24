#include "Item.h"

#include "GameSceneParam.h"
#include "DxLib.h"



Item::Item(GameObjContainer* ow, Vec2D<int> pos, int graph, bool visible)
	:mGraphID(graph),
	GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}),
	mIsVisible(visible)
{}


void Item::draw(){
	if(mIsVisible){
		DrawGraph(mPos.x, mPos.y, mGraphID, true);
	}
}


// true��Ԃ��Ǝd�l����ăX�g�b�N����폜�����
bool Item::use(){

	return true;
}