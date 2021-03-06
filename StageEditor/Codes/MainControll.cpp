#include "MainControll.h"

#include "DxLib.h"
#include "Param.h"
#include "InputManager.h"
#include <Windows.h>


MainControll::MainControll(){

	// ボタンの設定
	Vec2D<int> btnSize = {100, 30};
	int midPosX = Param::STAGE_FRAME_SIZE.x + (Param::RIGHT_FRAME_SIZE.x / 2);
	int baseY	= 70 - (btnSize.y / 2);
	mOpenStageBtn = new Button(Vec2D<int>(midPosX - btnSize.x, baseY), btnSize, "OPEN");
	mSaveStageBtn = new Button(Vec2D<int>(midPosX, baseY), btnSize, "SAVE");

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

	// 背景
	DrawBox(0, 0, 920, Param::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	DrawBox(920, 0, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, GetColor(50, 50, 50), true);

	// ボタン
	mOpenStageBtn->draw();
	mSaveStageBtn->draw();

	mMaterialMaps.at(mCurrentTabID)->draw();
	mStage->draw();
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

		mMaterialMaps.at(mCurrentTabID)->clickDetectAndAction();

		// ステージ上のマスがクリックされたらmMaterialTabで選択されている要素を置く
		if(mStage->clickDetectAndAction()){	
			mStage->putDataToClickedTile(mMaterialMaps.at(mCurrentTabID)->getMassData());
		}

		// タブの切り替えが必要かを判定
		mCurrentTabID = mStage->checkCurrentTab();

		draw();
	}

}