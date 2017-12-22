#include "GraphManager.h"

#include "DxLib.h"
#include "FileUtils.h"
#include <vector>


#define MATERIAL_DATA_DIR "Res/Graph/"

// MATERIAL_DATA_DIR下に存在する
#define CHARA_DIR "Chara/"
#define ITEM_DIR "Item/"
#define MASS_40_DIR "Mass/h40/"
#define MASS_60_DIR "Mass/h60/"

GraphManager::~GraphManager(){

	for(auto i = mVec.begin(); i != mVec.end(); i++){

		for(auto elem = mVec[i->first].begin(); elem != mVec[i->first].end(); elem++){
			DeleteGraph(elem->gid);
		}
	}

}


void loadResToMap(std::vector<graph_info> &vec, std::string path, bool is60h = false){

	int gHeight = (is60h ? 60 : Param::MASS_SIZE);

	std::vector<std::string> files = FileUtils::readPathInDir(path);
	for(auto i = files.begin(); i != files.end(); i++){
		int loadG = LoadGraph((*i).c_str());
		if(loadG != -1){

			// 画像サイズから何分割のデータなのかを計算
			Vec2D<int> size;
			GetGraphSize(loadG, &(size.x), &(size.y));
			int xNum = size.x / Param::MASS_SIZE;
			int yNum = size.y / gHeight;
			int *graphIDs = new int[yNum * xNum];

			// 分割画像を各メモリに読み込む
			LoadDivGraph((*i).c_str(), yNum * xNum, xNum, yNum, Param::MASS_SIZE, gHeight, graphIDs);
			for(int y = 0; y < yNum; y++){
				for(int x = 0; x < xNum; x++){
					graph_info tmp;
					tmp.gid = graphIDs[y * xNum + x];
					tmp.is60h = is60h;
					tmp.path = (*i);
					tmp.point = Vec2D<int>(x * Param::MASS_SIZE, y * gHeight);
					vec.push_back(tmp);
				}
			}
		
			DeleteGraph(loadG);
			delete[] graphIDs;
		}
	}
}


// MATERIAL_DATA_DIR下の各フォルダ内にあるリソースを読み込む
void GraphManager::load(){

	loadResToMap((mVec[map_id::MASS]),	std::string(MATERIAL_DATA_DIR) + MASS_40_DIR);
	loadResToMap((mVec[map_id::MASS]),	std::string(MATERIAL_DATA_DIR) + MASS_60_DIR, true);
	loadResToMap((mVec[map_id::CHARA]), std::string(MATERIAL_DATA_DIR) + CHARA_DIR,	true);
	loadResToMap((mVec[map_id::ITEM]),  std::string(MATERIAL_DATA_DIR) + ITEM_DIR);
}


std::vector<int> GraphManager::getAllIDFromVec(map_id mapId){
	std::vector<int> rtn;
	for(auto i = mVec[mapId].begin(); i != mVec[mapId].end(); i++){
		rtn.push_back(i->gid);
	}
	return rtn;
}


graph_info GraphManager::searchInfoFromMap(int gID, map_id mapId){
	
	try{
		for(graph_info info : mVec.at(mapId)){
			if(info.gid == gID){
				return info;
			}
		}
	}
	catch(std::out_of_range){}

	graph_info tmp;
	return tmp;
}


int GraphManager::checkGID(std::string path, Vec2D<int> point, map_id mapId){

	try{
		for(graph_info info : mVec.at(mapId)){
			if(info.path == path && info.point == point){
				return info.gid;
			}
		}
	}
	catch(std::out_of_range){}

	return -1;
}