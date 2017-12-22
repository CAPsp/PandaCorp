#include "MaterialTab.h"

#include "DxLib.h"
#include "Param.h"
#include "InputManager.h"


MaterialTab::MaterialTab(map_id id){

	mMassGraphID = GraphManager::getInstance().getAllIDFromVec(id);
	mMassGraphID.insert(mMassGraphID.begin(), -1);	// �����S���p�̋�}�X

	mOrigin = {Param::STAGE_FRAME_SIZE.x, 100};

	// �}�X�����u���邩���v�Z
	int x, y;
	for(y = 0; (y * Param::MASS_SIZE) < Param::RIGHT_FRAME_SIZE.y; y++);
	for(x = 0; (x * Param::MASS_SIZE) < Param::RIGHT_FRAME_SIZE.x; x++);
	mMassNum = {x, y};
}


void MaterialTab::clickDetectAndAction(){

	// �N���b�N���ꂽ�Ƃ��̃}�X�O���t�B�b�N��I����ԂƂ���
	if(InputManager::getInstance().isUpMouseLeft()){
		for(int y = 0; y < mMassNum.y; y++){
			for(int x = 0; x < mMassNum.y; x++){

				Vec2D<int> c1 = { mOrigin.x + (x * Param::MASS_SIZE),		mOrigin.y + (y * Param::MASS_SIZE)};
				Vec2D<int> c2 = { mOrigin.x + ((x + 1) * Param::MASS_SIZE), mOrigin.y + ((y + 1) * Param::MASS_SIZE)};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					// mMassGraphID�̉��Ԗڂɓ����Ă���̂����t�Z
					int elem = (y * mMassNum.x) + x;
					if(elem < mMassGraphID.size()){
						mSelectDataGID = mMassGraphID[elem];
					}
				}
			}
		}

	}

}


void MaterialTab::draw(){

	// �}�X�O���t�B�b�N
	std::vector<int>::iterator itr = mMassGraphID.begin();
	for(int y = 0; y < mMassNum.y; y++){
		for(int x = 0; x < mMassNum.x; x++){
			
			if(itr != mMassGraphID.end()){

				// �I������Ă����ꍇ�̓n�C���C�g
				if(mSelectDataGID == (*itr)){
					DrawBox(mOrigin.x + (x * Param::MASS_SIZE),
							mOrigin.y + (y * Param::MASS_SIZE),
							mOrigin.x + ((x + 1) * Param::MASS_SIZE),
							mOrigin.y + ((y + 1) * Param::MASS_SIZE),
							GetColor(255, 0, 0),
							true);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					
				}

				// �O���t�B�b�N�̉�����(40�~40)������������悤�ɕ`��
				Vec2D<int> gSize;
				GetGraphSize(*itr, &(gSize.x), &(gSize.y));
				DrawRectGraph(mOrigin.x + (x * Param::MASS_SIZE),
							  mOrigin.y + (y * Param::MASS_SIZE),
							  gSize.x - Param::MASS_SIZE,
							  gSize.y - Param::MASS_SIZE,
							  Param::MASS_SIZE,
							  Param::MASS_SIZE,
							  (*itr),
							  false,
							  false);

				if(mSelectDataGID == (*itr)){
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
				}

				itr++;
			}
			else{
				// �Ή�����}�X�����݂��Ȃ��ꍇ�͐����߂�
				DrawBox(mOrigin.x + (x * Param::MASS_SIZE),
						mOrigin.y + (y * Param::MASS_SIZE),
						mOrigin.x + ((x+1) * Param::MASS_SIZE),
						mOrigin.y + ((y+1) * Param::MASS_SIZE),
						GetColor(0, 0, 255),
						true);
			}

		}
	}

	// �i�q
	int lineColor = GetColor(0, 255, 0);
	DrawBox(mOrigin.x, mOrigin.y, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, lineColor, false);
	for(int x = 1; x < mMassNum.x; x++){
		DrawLine(mOrigin.x + (x * Param::MASS_SIZE),
				 mOrigin.y,
				 mOrigin.x + (x * Param::MASS_SIZE),
				 Param::RIGHT_FRAME_SIZE.y,
				 lineColor);
	}

	for(int y = 1; y < mMassNum.y; y++){
		DrawLine(mOrigin.x,
				 mOrigin.y + (y * Param::MASS_SIZE),
				 Param::WINDOW_SIZE.x,
				 mOrigin.y + (y * Param::MASS_SIZE),
				 lineColor);
	}
}