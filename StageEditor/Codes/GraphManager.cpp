#include "GraphManager.h"

#include "DxLib.h"
#include "FileUtils.h"
#include <vector>
#include "Param.h"


GraphManager::~GraphManager(){

	for(auto i = mMassMap.begin(); i != mMassMap.end(); i++){
		DeleteGraph(i->second);
	}
	for(auto i = mCharaMap.begin(); i != mCharaMap.end(); i++){
		DeleteGraph(i->second);
	}
	for(auto i = mItemMap.begin(); i != mItemMap.end(); i++){
		DeleteGraph(i->second);
	}
}


void loadResToMap(std::map<std::string, int> *map, std::string path){
	
	for(auto i = map->begin(); i != map->end(); i++){
		DeleteGraph(i->second);
	}
	map->erase(map->begin(), map->end());

	std::vector<std::string> files = FileUtils::readPathInDir(path);
	for(auto i = files.begin(); i != files.end(); i++){
		int tmp = LoadGraph((*i).c_str());
		if(tmp != -1){
			(*map)[*i] = tmp;
		}
	}
}


// MATERIAL_DATA_DIR下の各フォルダ内にあるリソースを読み込む
void GraphManager::load(){

	loadResToMap(&mCharaMap, std::string(MATERIAL_DATA_DIR) + CHARA_DIR);
	loadResToMap(&mItemMap,  std::string(MATERIAL_DATA_DIR) + ITEM_DIR);
	loadResToMap(&mMassMap,  std::string(MATERIAL_DATA_DIR) + MASS_DIR);
}


std::vector<int> getAllFromMap(const std::map<std::string, int>* map){
	std::vector<int> rtn;
	for(auto i = map->begin(); i != map->end(); i++){
		rtn.push_back(i->second);
	}
	return rtn;
}


std::vector<int> GraphManager::getAllMassID(){
	return getAllFromMap(&mMassMap);
}


std::vector<int> GraphManager::getAllCharaID(){
	return getAllFromMap(&mCharaMap);
}


std::vector<int> GraphManager::getAllItemID(){
	return getAllFromMap(&mItemMap);
}