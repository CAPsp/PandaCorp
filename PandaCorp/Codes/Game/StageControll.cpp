#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mMasses);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
	}

	mObjects.push_back(new Player(100, 100));
}


StageControll::~StageControll(){}


void StageControll::update(){

	// 1�t���[�����̍X�V����
	for(auto mass : mMasses){ mass->update();	}
	for(auto obj : mObjects){ obj->update();	}

	// �����蔻�菈��
	for(auto obj : mObjects){

		// �}�X�Ƃ̂����蔻��
		for(auto mass : mMasses){

			if(obj->checkCollide(mass)){
				obj->hit(mass);
				mass->hit(obj);
			}
		}

		// ���I�u�W�F�N�g�Ƃ̂����蔻��
		for(auto other : mObjects){
			if(other == obj){ continue; }

			if(obj->checkCollide(other)){
				obj->hit(other);
				other->hit(obj);
			}
		}

	}

	// �}�X�̓��C���[���ɕ`�揈�����s��
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		for(auto mass : mMasses){
			mass->draw(i);
		}
	}
	for(auto obj : mObjects){
		obj->draw(0);
	}

}
