#include "StageFile.h"

#include "picojson.h"
#include "GraphManager.h"
#include "GameSceneParam.h"
#include "Mass.h"
#include "Enemy.h"
#include "Player.h"
#include "FileUtils.h"
#include "Item.h"


StageFile::StageFile(std::string path)
	:mFilePath(path){}


// json�t�@�C���̎d�l�̓G�f�B�^�[�Ɛ�������ۂK�v�����邽�ߕύX�����\��������
std::string StageFile::read(GameObjContainer* container, int& score){

	picojson::value v;
	std::string err = FileUtils::openJson(mFilePath, v);
	if(err != ""){
		return err;
	}

	// �}�X�̓ǂݍ���
	int yCnt = 0;
	picojson::array yArr = (picojson::value(v.get<picojson::object>()["Masses"])).get<picojson::array>();
	for(auto yItr = yArr.begin(); yItr != yArr.end(); yItr++){

		int xCnt = 0;
		picojson::array xArr = picojson::value(*yItr).get<picojson::array>();
		for(auto xItr = xArr.begin(); xItr != xArr.end(); xItr++){
			picojson::object massObj = picojson::value(*xItr).get<picojson::object>();

			std::vector<int> massIDs;
			for(int i = 0; i < 3; i++){
				picojson::object elemObj = picojson::value(massObj.at(std::to_string(i))).get<picojson::object>();
				std::string path = elemObj.at("path").get<std::string>();
				Vec2D<int> gPoint = Vec2D<int>( (int)(elemObj.at("x").get<double>()), (int)(elemObj.at("y").get<double>()));
				//bool is60h = elemObj.at("60px").get<bool>();
				int id = GraphManager::getInstance().checkID(path, gPoint);
				if(id == -1){ continue; }

				// �}�X��z�u���钆�S�_�����W�Ƃ��ēn��
				massIDs.push_back(id);
			}

			Mass::mass_elem elem = Mass::mass_elem::NORMAL;
			if(massObj.at("obstacle").get<bool>()){
				elem = Mass::mass_elem::OBSTACLE;
			}
			if(!massObj.at("pass").get<bool>()){
				elem = Mass::mass_elem::NOT_PASS;
			}
			
			// ��ԏ�ɑ��݂���}�X�ɂ͑�����ݒ肷��̂Œ���
			for(int i = 0; i < massIDs.size(); i++){

				if(i == massIDs.size() - 1){

					int containerId = (elem == Mass::mass_elem::NORMAL) ? 0 : 1;
					container[containerId].add(	new Mass(&(container[containerId]),
												Vec2D<int>((xCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2), (yCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2)),
												massIDs[i],
												elem));
				}
				else{
					Mass* tmp = new Mass(	&(container[0]),
											Vec2D<int>((xCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2), (yCnt * GameSceneParam::MASS_SIZE) + (GameSceneParam::MASS_SIZE / 2)),
											massIDs[i]);
					container[0].add(tmp);
				}

			}

			// �A�C�e���ǂݍ��ݏ���
			picojson::object itemObj = picojson::value(massObj.at("item")).get<picojson::object>();
			std::string path = itemObj.at("path").get<std::string>();
			Vec2D<int> point = {(int)(itemObj.at("x").get<double>()), (int)(itemObj.at("y").get<double>())};
			int id = GraphManager::getInstance().checkID(path, point);
			if(id != -1){
				container[1].add(new Item(&(container[1]),
										  Vec2D<int>((xCnt * GameSceneParam::MASS_SIZE), (yCnt * GameSceneParam::MASS_SIZE)),
										  id));
			}

			xCnt++;
		}

		yCnt++;
	}

	// �G�̓ǂݍ���
	picojson::array enemyArr = (v.get<picojson::object>()["Enemy"]).get<picojson::array>();
	for(auto enemy = enemyArr.begin(); enemy != enemyArr.end(); enemy++){
		picojson::array patrolArr = enemy->get<picojson::array>();
		std::vector<Vec2D<int>> patrolVec;
		for(auto point = patrolArr.begin(); point != patrolArr.end(); point++){
			picojson::array pointArr = point->get<picojson::array>();

			Vec2D<int> p;
			p.x = (int)(pointArr.at(0).get<double>()) * GameSceneParam::MASS_SIZE + (GameSceneParam::MASS_SIZE / 2);
			p.y = (int)(pointArr.at(1).get<double>()) * GameSceneParam::MASS_SIZE + (GameSceneParam::MASS_SIZE / 2);
			patrolVec.push_back(p);
		}

		container[1].add(new Enemy(&container[1], patrolVec));
	}

	// �v���C���[�������W�̓ǂݍ���
	picojson::object playerObj = (v.get<picojson::object>()["Player"]).get<picojson::object>();
	int x = (int)(playerObj.at("x").get<double>()) * GameSceneParam::MASS_SIZE + (GameSceneParam::MASS_SIZE / 2);
	int y = (int)(playerObj.at("y").get<double>()) * GameSceneParam::MASS_SIZE + (GameSceneParam::MASS_SIZE / 2);
	container[1].add(new Player(&container[1], Vec2D<int>(x, y)));

	// �ō��X�R�A�ǂݍ���
	score = (int)((v.get<picojson::object>()["Score"]).get<double>());

	return "";
}