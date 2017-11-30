#include "MainControll.h"

#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "Param.h"
#include "InputManager.h"
#include "Button.h"
#include <Windows.h>


Button fileReadBtn(Vec2D<int>(100, 100), Vec2D<int>(300, 300), "（ ＾ω＾）");


void draw(){

	// 背景
	DrawBox(0, 0, 920, Param::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	DrawBox(920, 0, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, GetColor(50, 50, 50), true);

	fileReadBtn.draw();

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

		// ファイル選択ダイアログを使ってファイルを選択
		if(fileReadBtn.update()){

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
				MessageBox(NULL, filePath, "Debug", MB_OK);
			}

		}

		draw();

	}

}