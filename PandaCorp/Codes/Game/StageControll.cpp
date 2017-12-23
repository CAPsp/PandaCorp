#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"
#include "Enemy.h"


//const int lay = GameSceneParam::MASS_GRAPH_LAYER_NUM;


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects, mHighScore);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
	}

	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}
}


StageControll::~StageControll(){}


void StageControll::update(){
	
	// 1�t���[�����̍X�V����
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->update();
		}
	}

	// �I�u�W�F�N�g���m�̂����蔻�������	
	for(int i = 0; i < mObjects[1].checkSize(); i++){
		for(int j = 0; j < mObjects[1].checkSize(); j++){

			if(i == j && i == j){ continue; }

			// �}�X���m�̂����蔻��͍l�����Ȃ�
			if( (dynamic_cast<Mass*>(mObjects[1].checkElem(i)) != NULL) &&
				(dynamic_cast<Mass*>(mObjects[1].checkElem(j)) != NULL) ){
				continue;
			}

			if( mObjects[1].checkElem(i)->checkCollide( mObjects[1].checkElem(j) ) ){
				mObjects[1].checkElem(i)->hit(mObjects[1].checkElem(j));
				mObjects[1].checkElem(j)->hit(mObjects[1].checkElem(i));
			}
		}
	}

	// �R���e�i�̍X�V�����i�ǉ��A�폜�A�`�揇�\�[�g�����̂��߂ɕK�{�j
	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}

	// ���C���[���ɕ`�揈�����s��
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}

}
