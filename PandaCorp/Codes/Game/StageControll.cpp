#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Player.h"
#include "Mass.h"
#include "Enemy.h"
#include "Item.h"
#include "GraphManager.h"
#include "ItemInfoDef.h"
#include "ItemStock.h"



StageControll::StageControll(std::string jsonPath)
	:mStageFile(jsonPath){
	
	std::string msg = mStageFile.read(mObjects, mHighScore);
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "�G���[", MB_OK);
	}

	// �X�e�[�W�O�ɂłȂ����߂̂����蔻������
	Vec2D<int> fSize = {GameSceneParam::STAGE_FRAME_SIZE.x, GameSceneParam::STAGE_FRAME_SIZE.y};
	Vec2D<int> pos[4] = {	Vec2D<int>(fSize.x / 2, -10), Vec2D<int>(fSize.x / 2, fSize.y + 10),
							Vec2D<int>(-10, fSize.y / 2), Vec2D<int>(fSize.x + 10, fSize.y / 2)};
	Vec2D<int> size[4] = {	Vec2D<int>(fSize.x, 20), Vec2D<int>(fSize.x, 20),
							Vec2D<int>(20, fSize.y), Vec2D<int>(20, fSize.y)};
	for(int i = 0; i < 4; i++){
		Mass* tmp = new Mass(&(mObjects[1]), Vec2D<int>(0, 0), -1, Mass::mass_elem::NOT_PASS);
		tmp->changeHitAreaCenter(pos[i]);
		tmp->changeHitAreaSize(size[i]);
		mObjects[1].add(tmp);
	}

	for(int i = 0; i < 2; i++){
		mObjects[i].update();
	}

	// �X�e�[�W���Ɍ����Ȃ��Ƃ��͎������Ɍ���ǉ�����
	bool flag = false;
	for(int i = 0; i < mObjects[1].checkSize(); i++){
		Item* tmp = dynamic_cast<Item*>(mObjects[1].checkElem(i));
		if(tmp != NULL &&
		   tmp->checkGID() == GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::KEY_POS)){

			flag = true;
			break;
		}
	}
	if(!flag){
		ItemStock::addItem(new Item(nullptr,
									Vec2D<int>(0, 0),
									GraphManager::getInstance().checkID(ItemInfo::PATH, ItemInfo::KEY_POS),
									true));
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
	
}


void StageControll::draw(){
	// ���C���[���ɕ`�揈�����s��
	for(int i = 0; i < 2; i++){
		for(int num = 0; num < mObjects[i].checkSize(); num++){
			mObjects[i].checkElem(num)->draw();
		}
	}
}


// ���݂̔z�u���Ă�}�X����G�ꂽ��N���A�ł���}�X�����邩�ǂ����𒲍�
void StageControll::checkExistClearMass(const ItemStock& itemStock){

	for(int i = 0; i < mObjects[1].checkSize(); i++){
		if(dynamic_cast<Mass*>(mObjects[1].checkElem(i)) != NULL){

			Mass tmp = *(dynamic_cast<Mass*>(mObjects[1].checkElem(i)));

			if(itemStock.checkClearCurrentStock(tmp)){
				(dynamic_cast<Mass*>(mObjects[1].checkElem(i)))->toClearMass();
			}
		}
	}

}