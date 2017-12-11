#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"


const int lay = GameSceneParam::MASS_GRAPH_LAYER_NUM;


StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
	}

	mObjects[lay].add(new Player(&mObjects[lay], Vec2D<int>(100, 100) ));

	for(int i = 0; i <= lay; i++){
		mObjects[i].update();
	}
}


StageControll::~StageControll(){}


void StageControll::update(){
	
	// 1�t���[�����̍X�V����
	for(int i = 0; i <= lay; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->update();
		}
	}

	// ���C���[1�ȏ�̂��̑S�ĂŃI�u�W�F�N�g���m�̂����蔻�������
	for(int i = 1; i < lay; i++){
		for(int j = i + 1; j <= lay; j++){

			for(int numI = 0; numI < mObjects[i].checkSize(); numI++){
				for(int numJ = 0; numJ < mObjects[j].checkSize(); numJ++){

					if( mObjects[i].checkElem(numI)->checkCollide( mObjects[j].checkElem(numJ) ) ){
						mObjects[i].checkElem(numI)->hit(mObjects[j].checkElem(numJ));
						mObjects[j].checkElem(numJ)->hit(mObjects[i].checkElem(numI));
					}
				}
			}

		}
	}

	// ���C���[���ɕ`�揈�����s��
	for(int i = 0; i <= lay; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}

	// �R���e�i�̍X�V�����i�ǉ��A�폜�����̂��߂ɕK�{�j
	for(int i = 0; i <= lay; i++){
		mObjects[i].update();
	}

}
