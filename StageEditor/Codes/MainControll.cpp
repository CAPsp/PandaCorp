#include "MainControll.h"

#include "DxLib.h"
#include "Param.h"
#include "InputManager.h"
#include <Windows.h>


MainControll::MainControll(){

	// �{�^���̐ݒ�
	Vec2D<int> btnSize = {100, 30};
	Vec2D<int> basePoint = {(Param::STAGE_FRAME_SIZE.x + (Param::RIGHT_FRAME_SIZE.x / 4)) - (btnSize.x / 2),
							70 - (btnSize.y / 2)};
	mOpenStageBtn = new Button(basePoint, basePoint + btnSize, "OPEN");
	basePoint.x = (Param::STAGE_FRAME_SIZE.x + (Param::RIGHT_FRAME_SIZE.x / 4 * 3)) - (btnSize.x / 2);
	mSaveStageBtn = new Button(basePoint, basePoint + btnSize, "SAVE");

	mMaterialMaps[map_id::MASS] = new MaterialTab(map_id::MASS);
	mMaterialMaps[map_id::ITEM] = new MaterialTab(map_id::ITEM);
	mMaterialMaps[map_id::CHARA] = new MaterialTab(map_id::CHARA);
	mCurrentTabID = map_id::MASS;

	mStage = new Stage();
}


MainControll::~MainControll(){
	delete mStage;			mStage = nullptr;
	delete mOpenStageBtn;	mOpenStageBtn = nullptr;
	delete mSaveStageBtn;	mSaveStageBtn = nullptr;
	for(auto itr = mMaterialMaps.begin(); itr != mMaterialMaps.end(); itr++){
		delete itr->second;
	}
}


void MainControll::draw(){

	// �w�i
	DrawBox(0, 0, 920, Param::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	DrawBox(920, 0, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, GetColor(50, 50, 50), true);

	// �{�^��
	mOpenStageBtn->draw();
	mSaveStageBtn->draw();

	mMaterialMaps.at(mCurrentTabID)->draw();
	mStage->draw();
}


// �t�@�C���I���_�C�A���O��\�����A�I�������t�@�C���̃p�X��Ԃ�
std::string openFileDialog(){

	const int MAX_SIZE = 1000;
	char filePath[MAX_SIZE] = "";

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = TEXT("�S�Ẵt�@�C��(*.*)\0*.*\0\0");
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = MAX_SIZE;
	ofn.lpstrInitialDir = GEN_DATA_DIR;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_EXPLORER;

	if(GetOpenFileName(&ofn)){
		return filePath;
	}

	return "";
}


void MainControll::doLoop(){

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

		InputManager::getInstance().update();

		/*
		// �t�@�C���I���_�C�A���O���g���ĊJ���t�@�C����I��
		if(mOpenStageBtn->update()){

			std::string path = openFileDialog();
			if(path != ""){
				delete mStage;	mStage = nullptr;
				mStage = new Stage(path);
				MessageBox(NULL, (std::string(path) + "���J���܂���").c_str(), "�_�C�A���O", MB_OK);
			}
		}

		// �t�@�C�������w�肵�ĕۑ�
		if(mSaveStageBtn->update()){

			std::string path = openFileDialog();
			if(path != ""){
				mStage->save(path);
				MessageBox(NULL, (std::string(path) + "�ɕۑ����܂���").c_str(), "�_�C�A���O", MB_OK);
			}
		}
		*/

		mMaterialMaps.at(mCurrentTabID)->clickDetectAndAction();

		// �X�e�[�W��̃}�X���N���b�N���ꂽ��mMaterialTab�őI������Ă���v�f��u��
		if(mStage->clickDetectAndAction()){	
			mStage->putDataToClickedTile(mMaterialMaps.at(mCurrentTabID)->getMassData());
		}

		// �^�u�̐؂�ւ����K�v���𔻒�
		mCurrentTabID = mStage->checkCurrentTab();

		draw();
	}

}