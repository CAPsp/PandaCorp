#include "MainControll.h"

#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "Param.h"
#include "InputManager.h"
#include <Windows.h>


MainControll::MainControll(){

	// ボタンの設定
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

	// 背景
	DrawBox(0, 0, 920, Param::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	DrawBox(920, 0, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, GetColor(50, 50, 50), true);

	// ボタン
	mOpenStageBtn->draw();
	mSaveStageBtn->draw();
}


// ファイル選択ダイアログを表示し、選択したファイルのパスを返す
std::string openFileDialog(){

	const int MAX_SIZE = 1000;
	char filePath[MAX_SIZE] = "";

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = TEXT("全てのファイル(*.*)\0*.*\0\0");
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

		// ファイル選択ダイアログを使って開くファイルを選択
		if(mOpenStageBtn->update()){

			std::string path = openFileDialog();
			if(path != ""){
				delete mStage;	mStage = nullptr;
				mStage = new Stage(path);
				MessageBox(NULL, (std::string(path) + "を開きました").c_str(), "ダイアログ", MB_OK);
			}
		}
		
		// ファイル名を指定して保存
		if(mSaveStageBtn->update()){

			std::string path = openFileDialog();
			if(path != ""){
				mStage->save(path);
				MessageBox(NULL, (std::string(path) + "に保存しました").c_str(), "ダイアログ", MB_OK);
			}
		}

		draw();
	}

}