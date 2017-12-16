#include "Mass.h"

#include "GameSceneParam.h"
#include "DxLib.h"


Mass::Mass(GameObjContainer* ow, Vec2D<int> pos, int graph, bool pass)
	:mGraph(graph), mPass(pass),
	GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}){}


void Mass::draw(){

	Vec2D<int> gSize;
	GetGraphSize(mGraph, &gSize.x, &gSize.y);

	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
					mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
					1.0, 0, mGraph, true);
	
}


void Mass::hit(GameObj*){}