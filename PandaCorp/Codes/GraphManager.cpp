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


// Mapに格納した対応するリソースＩＤを返す
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


// Mapに格納した対応するリソースＩＤを返す
int GraphManager::checkID(std::string name){

	try{
		return mMap.at(name);
	}
	catch(std::out_of_range){	// 存在しなかった場合
		return -1;
	}
}