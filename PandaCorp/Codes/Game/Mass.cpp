#include "Mass.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "SpecialMassDef.h"
#include "GraphManager.h"


Mass::Mass(GameObjContainer* ow, Vec2D<int> pos, int graph, mass_elem elem)
	:mGraph(graph),
	mElem(elem),
	GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}){

	// ƒhƒA‚©‚Ç‚¤‚©
	for(Vec2D<int> p : SpecialMass::DOOR_GRAPH_POS){
		if(mGraph == GraphManager::getInstance().checkID(SpecialMass::DOOR_GRAPH_PATH, p)){
			mIsDoor = true;
		}
	}

	// ‘‹‚©‚Ç‚¤‚©
	for(Vec2D<int> p : SpecialMass::WINDOW_GRAPH_POS){
		if(mGraph == GraphManager::getInstance().checkID(SpecialMass::WINDOW_GRAPH_PATH, p)){
			mIsWindow = true;
		}
	}
}


void Mass::draw(){

	Vec2D<int> gSize;
	GetGraphSize(mGraph, &gSize.x, &gSize.y);

	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
					mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
					1.0, 0, mGraph, true);
	
}
