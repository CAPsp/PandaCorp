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


// 画像から渡されたアニメーション数に応じた領域を抜き出し、新たなグラフィックハンドルとして生成する
// 抜き出せない場合-1が返る
int GraphManager::getDerivGraph(std::string path, int num, int w){

	int id = checkID(path);
	if(id == -1){ return -1; }

	int width, height;
	GetGraphSize(id, &width, &height);
	id = DerivationGraph(w * num, 0, w, height, id);

	return id;
}