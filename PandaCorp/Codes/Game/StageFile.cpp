#include "StageFile.h"

#include <fstream>
#include "picojson.h"
#include "GraphManager.h"
#include "GameSceneParam.h"
#include "Mass.h"


StageFile::StageFile(std::string path)
	:mFilePath(path){}


std::string openJson(std::string path, picojson::value& v){
	
	std::ifstream ifs(path);
	if(!ifs.is_open()){
		return (path + "���J���܂���ł���");
	}
	return picojson::parse(v, ifs);
}


// json�t�@�C���̎d�l�̓G�f�B�^�[�Ɛ�������ۂK�v�����邽�ߕύX�����\��������
std::string StageFile::read(GameObjContainer* container){

	picojson::value v;
	std::string err = openJson(mFilePath, v);
	if(err != ""){
		return err;
	}

	int yCnt = 0;
	picojson::array yArr = (picojson::value(v.get<picojson::object>()["Masses"])).get<picojson::array>();
	for(auto yItr = yArr.begin(); yItr != yArr.end(); yItr++){

		int xCnt = 0;
		picojson::array xArr = picojson::value(*yItr).get<picojson::array>();
		for(auto xItr = xArr.begin(); xItr != xArr.end(); xItr++){
			picojson::object obj = picojson::value(*xItr).get<picojson::object>();

			for(int i = 0; i < GameSceneParam::MASS_GRAPH_LAYER_NUM - 1; i++){
				std::string valueName = "mass_" + std::to_string(i);
				int id = GraphManager::getInstance().checkID(obj.at(valueName).get<std::string>());
				if(id == -1){ continue; }

				bool pass = false;
				pass = obj.at("pass").get<bool>();

				// �}�X��z�u���钆�S�_�����W�Ƃ��ēn��
				Mass* mass = new Mass(&(container[i]),
									  Vec2D<int>((xCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2), (yCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2)),
									  id,
									  pass);

				container[i].add(mass);
			}

			// TODO: �A�C�e���̏���
			//graph.push_back(-1);

			xCnt++;
		}

		yCnt++;
	}

	return "";
}