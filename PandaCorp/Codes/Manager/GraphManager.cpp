#include "GraphManager.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "FileUtils.h"
#include <vector>



GraphManager::~GraphManager(){
	for(auto i = mMap.begin(); i != mMap.end(); i++){
		DeleteGraph(i->second);
	}
}


// Map‚ÉŠi”[‚µ‚½‘Î‰‚·‚éƒŠƒ\[ƒX‚h‚c‚ğ•Ô‚·
void GraphManager::load(){


	for(auto i = mMap.begin(); i != mMap.end(); i++){
		DeleteGraph(i->second);
	}
	mMap.erase(mMap.begin(), mMap.end());

	std::vector<std::string> files = FileUtils::readPathBelowDir(GRAPH_DIR_PATH);
	for(auto i = files.begin(); i != files.end(); i++){
		int tmp = LoadGraph((*i).c_str());
		if(tmp != -1){
			mMap[*i] = tmp;
		}
	}

	bool debug = 0;
	debug++;
}


// Map‚ÉŠi”[‚µ‚½‘Î‰‚·‚éƒŠƒ\[ƒX‚h‚c‚ğ•Ô‚·
// ˆø”‚É‚ÍGRAPH_DIR_PATH‚©‚ç‚Ì‘Š‘ÎƒpƒX‚ğw’è‚·‚é
int GraphManager::checkID(std::string name){

	name = GRAPH_DIR_PATH + name;

	try{
		return mMap.at(name);
	}
	catch(std::out_of_range){	// ‘¶İ‚µ‚È‚©‚Á‚½ê‡
		return -1;
	}
}