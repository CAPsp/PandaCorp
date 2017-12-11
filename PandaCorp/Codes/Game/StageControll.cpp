#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(&mMasses);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
	}

	mObjects.add(new Player(&mObjects, Vec2D<int>(100, 100) ));
}


StageControll::~StageControll(){}


void StageControll::update(){

	std::vector<GameObj*>& masses = mMasses.checkData();
	std::vector<GameObj*>& objs = mObjects.checkData();

	// 1�t���[�����̍X�V����
	for(auto mass : masses){ mass->update();	}
	for(auto obj : objs){ obj->update();	}

	// �����蔻�菈��
	for(auto obj : objs){

		// �}�X�Ƃ̂����蔻��
		for(auto mass : masses){

			if(obj->checkCollide(mass)){
				obj->hit(mass);
				mass->hit(obj);
			}
		}

		// ���I�u�W�F�N�g�Ƃ̂����蔻��
		for(auto other : objs){
			if(other == obj){ continue; }

			if(obj->checkCollide(other)){
				obj->hit(other);
				other->hit(obj);
			}
		}

	}

	// �}�X�̓��C���[���ɕ`�揈�����s��
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		
		// ���C���[2���O�ɑ��Q�[���I�u�W�F�N�g�͕`�悳���
		if(i == 1){
			for(auto obj : objs){
				obj->draw(0);
			}
		}
		
		for(auto mass : masses){
			mass->draw(i);
		}
	}

	// GameObj�����Ă���R���e�i�̍X�V�����i�ǉ��A�폜�����̂��߂ɕK�{�j
	mObjects.update();
	mMasses.update();

}
