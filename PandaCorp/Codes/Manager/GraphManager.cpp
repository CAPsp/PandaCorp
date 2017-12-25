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

	// �܂��f�B���N�g����ǂݍ���ŁA���̃f�B���N�g������size�t�@�C������摜�̕��ƍ����͉����m�F����
	std::vector<std::string> dirs = FileUtils::readDirPathBelowDir(GRAPH_DIR_PATH);
	for(std::string dir : dirs){

		// �摜���̕��ƍ�����ǂݍ���
		Vec2D<int> size;
		std::ifstream sizeFile(dir + "size");
		if(!sizeFile.is_open()){ continue; };
		sizeFile >> size.x >> size.y;

		std::vector<std::string> files = FileUtils::readPathBelowDir(dir);
		for(std::string file : files){
			int id = LoadGraph(file.c_str());
			if(id != -1){

				if(size.x != 0 && size.y != 0){

					// �摜�T�C�Y���牽�����̃f�[�^�Ȃ̂����v�Z
					Vec2D<int> divNum;
					GetGraphSize(id, &(divNum.x), &(divNum.y));
					divNum.x /= size.x;
					divNum.y /= size.y;

					// �����摜��ǂݍ���
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
				else{	// �T�C�Y0, 0�͂P�̑傫���摜�ł��邱�Ƃ�����
					mDatabase[file].push_back(std::pair<Vec2D<int>, int>(Vec2D<int>(0, 0), id));
				}
			}
		}
	}

}


// Map�Ɋi�[�����Ή����郊�\�[�X�h�c��Ԃ�
int GraphManager::checkID(std::string path, Vec2D<int> pos){

	try{
		for(auto itr : mDatabase.at(path)){
			if(itr.first == pos){
				return itr.second;
			}
		}
	}
	catch(std::out_of_range){}	// ���݂��Ȃ������ꍇ
	
	return -1;
}


// �����ɑΉ�����p�X���̉摜�Q��Ԃ�
// �A�j���[�V����������Ƃ��ȂǂɎg��
std::vector<int> GraphManager::getGraphIDs(std::string path){

	std::vector<int> vec;

	try{
		for(auto itr : mDatabase.at(path)){
			vec.push_back(itr.second);
		}
	}
	catch(std::out_of_range){}	// ���݂��Ȃ������ꍇ���vector���Ԃ�		
		
	return vec;
}