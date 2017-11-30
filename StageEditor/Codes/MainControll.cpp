#include "MainControll.h"

#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "Param.h"
#include "InputManager.h"
#include <Windows.h>


MainControll::MainControll(){

	// �{�^���̐ݒ�
	Vec2D<int> btnSize = {100, 30};
	Vec2D<int> basePoint = {1100 - 90 - (btnSize.x / 2), 20 - (btnSize.y / 2)};
	mOpenStageBtn = new Button(basePoint, basePoint + btnSize, "OPEN");
	basePoint.x = 1100 + 90 - (btnSize.x / 2);
	mSaveStageBtn = new Button(basePoint, basePoint + btnSize, "SAVE");
}


MainControll::~MainControll(){
	delete mStage;	mStage = nullptr;
	delete mOpenStageBtn;	mOpenStageBtn = nullptr;
	delete mSaveStageBtn;	mSaveStageBtn = nullptr;
}


void MainControll::draw(){

	// �w�i
	DrawBox(0, 0, 920, Param::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	DrawBox(920, 0, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, GetColor(50, 50, 50), true);

	// �{�^��
	mOpenStageBtn->draw();
	mSaveStageBtn->draw();
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

	picojson::value v;

	std::string err = picojson::parse(v, "{ \"slime\" : 1, \"kawaii\" : 2 }");
	if(!err.empty()){
		MessageBox(NULL, err.c_str(), "error", MB_OK);
	}

	std::ofstream ofs(std::string(GEN_DATA_DIR) + "test.json");

	ofs << v;

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

		InputManager::getInstance().update();

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

		draw();
	}

}