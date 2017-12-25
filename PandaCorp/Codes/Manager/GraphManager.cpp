#include "GraphManager.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "FileUtils.h"
#include <vector>
#include "GameSceneParam.h"
#include <fstream>



GraphManager::~GraphManager(){
	clear();
}


void GraphManager::clear(){
	for(auto map = mDatabase.begin(); map != mDatabase.end(); map++){
		for(auto itr = map->second.begin(); itr != map->second.end(); itr++){
			DeleteGraph(itr->second);
		}
		map->second.erase(map->second.begin(), map->second.end());
	}
	mDatabase.erase(mDatabase.begin(), mDatabase.end());

}


void GraphManager::load(){

	clear();

	// まずディレクトリを読み込んで、そのディレクトリ内のsizeファイルから画像の幅と高さは何か確認する
	std::vector<std::string> dirs = FileUtils::readDirPathBelowDir(GRAPH_DIR_PATH);
	for(std::string dir : dirs){

		// 画像内の幅と高さを読み込む
		Vec2D<int> size;
		std::ifstream sizeFile(dir + "size");
		if(!sizeFile.is_open()){ continue; };
		sizeFile >> size.x >> size.y;

		std::vector<std::string> files = FileUtils::readPathBelowDir(dir);
		for(std::string file : files){
			int id = LoadGraph(file.c_str());
			if(id != -1){

				if(size.x != 0 && size.y != 0){

					// 画像サイズから何分割のデータなのかを計算
					Vec2D<int> divNum;
					GetGraphSize(id, &(divNum.x), &(divNum.y));
					divNum.x /= size.x;
					divNum.y /= size.y;

					// 分割画像を読み込む
					int *graphs = new int[divNum.y * divNum.x];
					LoadDivGraph(file.c_str(), divNum.y * divNum.x, divNum.x, divNum.y, size.x, size.y, graphs);
					for(int y = 0; y < divNum.y; y++){
						for(int x = 0; x < divNum.x; x++){

							mDatabase[file].push_back(std::pair<Vec2D<int>, int>(Vec2D<int>(x * size.x, y * size.y), graphs[y * divNum.x + x]));
						}
					}

					DeleteGraph(id);
					delete[] graphs;
				}
				else{	// サイズ0, 0は１つの大きい画像であることを示す
					mDatabase[file].push_back(std::pair<Vec2D<int>, int>(Vec2D<int>(0, 0), id));
				}
			}
		}
	}

}


// Mapに格納した対応するリソースＩＤを返す
int GraphManager::checkID(std::string path, Vec2D<int> pos){

	try{
		for(auto itr : mDatabase.at(path)){
			if(itr.first == pos){
				return itr.second;
			}
		}
	}
	catch(std::out_of_range){}	// 存在しなかった場合
	
	return -1;
}


// 引数に対応するパス内の画像群を返す
// アニメーションさせるときなどに使う
std::vector<int> GraphManager::getGraphIDs(std::string path){

	std::vector<int> vec;

	try{
		for(auto itr : mDatabase.at(path)){
			vec.push_back(itr.second);
		}
	}
	catch(std::out_of_range){}	// 存在しなかった場合空のvectorが返る		
		
	return vec;
}