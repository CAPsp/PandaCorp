#include "DxLib.h"

#include <string>
#include "Param.h"
#include "MainControll.h"
#include "GraphManager.h"


std::string init(){

	setlocale(LC_ALL, "japanese");	//ロケール設定(ワイド文字使用のため必要)

	SetOutApplicationLogValidFlag(false);	// ログ出力を行わない

	// ウィンドウサイズとカラービット数を変更する
	if(SetGraphMode(Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, Param::COLOR_BIT_NUM) != DX_CHANGESCREEN_OK){
		return "ウィンドウサイズを変更できませんでした";
	}

	// フルスクリーン → ウィンドウ
	if(ChangeWindowMode(true) != DX_CHANGESCREEN_OK){
		return "ウィンドウモードへの移行に失敗しました";
	}

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1){
		return "DXライブラリの初期化処理で失敗しました";
	}

	SetDrawScreen(DX_SCREEN_BACK);	//描画先を裏画面に

	SetMainWindowText("ぱんだつ！: Stage Editor");	// ウィンドウの名前を変更

	SetFontSize(Param::FONT_SIZE);	// フォントサイズ変更

	GraphManager::getInstance().load(); // リソース読み込み

	return "";
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// 初期化処理 (失敗したらメッセージを表示して終了する)
	std::string msg = init();
	if(msg != ""){
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
		return -1;
	}

	// メインループ開始
	MainControll::getInstance().doLoop();


	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

