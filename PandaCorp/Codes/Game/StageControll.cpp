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

	// �}�X�̓��C���[���ɕ`�揈�����s��
	for(int i = 0; i < Mass::LAYER_NUM; i++){
		for(auto mass : mMasses){
			mass.draw(i);
		}
	}
	for(auto obj : mObjects){
		obj->update();
	}

	// TODO: �Q�[�����I�u�W�F�N�g���m�����蔻�菈��

}
