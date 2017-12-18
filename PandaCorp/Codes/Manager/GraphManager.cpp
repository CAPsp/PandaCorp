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


// Map�Ɋi�[�����Ή����郊�\�[�X�h�c��Ԃ�
int GraphManager::checkID(std::string name){

	try{
		return mMap.at(name);
	}
	catch(std::out_of_range){	// ���݂��Ȃ������ꍇ
		return -1;
	}
}


// �摜����n���ꂽ�A�j���[�V�������ɉ������̈�𔲂��o���A�V���ȃO���t�B�b�N�n���h���Ƃ��Đ�������
// �����o���Ȃ��ꍇ-1���Ԃ�
int GraphManager::getDerivGraph(std::string path, int num, int w){

	int id = checkID(path);
	if(id == -1){ return -1; }

	int width, height;
	GetGraphSize(id, &width, &height);
	id = DerivationGraph(w * num, 0, w, height, id);

	return id;
}