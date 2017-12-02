#include "GraphManager.h"

#include "DxLib.h"
#include "FileUtils.h"
#include <vector>
#include "Param.h"


GraphManager::~GraphManager(){

	for(auto i = mMap.begin(); i != mMap.end(); i++){

		for(auto elem = mMap[i->first].begin(); elem != mMap[i->first].end(); elem++){
			DeleteGraph(elem->second);
		}
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

	loadResToMap(&(mMap[map_id::MASS]),	 std::string(MATERIAL_DATA_DIR) + MASS_DIR);
	loadResToMap(&(mMap[map_id::CHARA]), std::string(MATERIAL_DATA_DIR) + CHARA_DIR);
	loadResToMap(&(mMap[map_id::ITEM]),  std::string(MATERIAL_DATA_DIR) + ITEM_DIR);
}


std::vector<int> GraphManager::getAllIDFromMap(map_id mapId){
	std::vector<int> rtn;
	for(auto i = mMap[mapId].begin(); i != mMap[mapId].end(); i++){
		rtn.push_back(i->second);
	}
	return rtn;
}


std::string GraphManager::searchPathFromMap(int id, map_id mapId){
	
	try{
		for(std::pair<std::string, int> elem : mMap.at(mapId)){
			if(elem.second == id){
				return elem.first;
			}
		}
	}
	catch(std::out_of_range){}

	return "";
}
