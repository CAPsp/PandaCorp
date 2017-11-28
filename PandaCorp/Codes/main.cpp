#include "DxLib.h"
#include <string>

#include "GlobalParam.h"
#include "MainControll.h"
#include "SoundManager.h"
#include "GraphManager.h"


std::string init();		// 初期化処理を担う 失敗で何かしらの文字列が返る
void end();				// 終了処理を担う


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// 初期化処理 (失敗したらメッセージを表示して終了する)
	std::string msg = init();
	if(msg != ""){ 
		MessageBox(NULL, msg.c_str(), "エラー", MB_OK);
		return -1;
	}

	// メインループ開始
	MainControll::getInstance().doMainLoop();

	end();	// 終了処理

	return 0;
}


std::string init(){

	setlocale(LC_ALL, "japanese");	//ロケール設定(ワイド文字使用のため必要)

	// ログ出力を行わない
	SetOutApplicationLogValidFlag(false);

	// ウィンドウサイズとカラービット数を変更する
	if(SetGraphMode(GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GlobalParam::COLOR_BIT_NUM) != DX_CHANGESCREEN_OK){
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

	SetMainWindowText(GAME_NAME);	// ウィンドウの名前を変更

	SetFontSize(GlobalParam::FONT_SIZE);	// デフォルトで使うフォントサイズを変更

	// リソースの読み込み
	SoundManager::getInstance().load();
	GraphManager::getInstance().load();

	return "";
}


void end(){

	//メモリに読み込んだグラフィックデータの開放
	InitGraph();
	InitMask();

	InitSoundMem();	//メモリに読み込んだサウンドデータの開放

	DxLib_End();
}