#include "Mass.h"

#include "GameSceneParam.h"
#include "DxLib.h"


Mass::Mass(int x, int y, std::vector<int> graphs, bool pass)
	:mPass(pass){

	if(graphs.size() != LAYER_NUM){
		throw std::exception("MassƒNƒ‰ƒX‚É•s“KØ‚Èˆø”‚ª“n‚³‚ê‚Ü‚µ‚½(‘æ‚Rˆø”)");
	}
	mGraphs = graphs;

	mPos.x = x;
	mPos.y = y;

	mHitAreaSize.x = GameSceneParam::MASS_SIZE;
	mHitAreaSize.y = GameSceneParam::MASS_SIZE;
}


void Mass::draw(int layer){

	if(layer >= LAYER_NUM){ return; }

	int id = mGraphs.at(layer);

	Vec2D<int> gSize;
	GetGraphSize(id, &gSize.x, &gSize.y);

	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
					mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
					1.0, 0, id, true);
	
}


void Mass::hit(GameObj& other){

}