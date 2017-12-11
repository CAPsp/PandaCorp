#include "Mass.h"

#include "GameSceneParam.h"
#include "DxLib.h"


Mass::Mass(GameObjContainer* ow, Vec2D<int> pos, std::vector<int> graphs, bool pass)
	:mPass(pass),
	 GameObj(ow, pos, Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)){

	if(graphs.size() != LAYER_NUM){
		throw std::exception("MassƒNƒ‰ƒX‚É•s“KØ‚Èˆø”‚ª“n‚³‚ê‚Ü‚µ‚½(‘æ‚Rˆø”)");
	}
	mGraphs = graphs;
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


void Mass::hit(GameObj*){}