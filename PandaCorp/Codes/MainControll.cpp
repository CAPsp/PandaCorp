#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"
#include "InputManager.h"

#include "GameScene.h"



MainControll::MainControll(){
	// デバッグ用
	mScene = new GameScene(0);
}


MainControll::~MainControll(){
	delete mScene;			mScene = nullptr;
	delete mChangeSceneMan;	mChangeSceneMan = nullptr;
}


// ゲームのメインループ処理
void MainControll::doMainLoop(){

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

		InputManager::getInstance().update();	// プレイヤーの入力を更新

		FPSManager::getInstance().adjustment();	// FPS調整
		
		if(mChangeSceneMan == nullptr){
			
			scene_sig signal = mScene->update();
			if(signal.next != scene_id::NONE){
				mChangeSceneMan = new ChangeSceneManager(mScene, signal);
			}
		}
		else{	// シーン遷移中
			if(mChangeSceneMan->update()){
				delete mChangeSceneMan;
				mChangeSceneMan = nullptr;
			}
		}

#ifdef _DEBUG
		int red = GetColor(255, 0, 0);

		// 左上に現在のFPSを表示
		DrawFormatString(0, 0, red, "%d", FPSManager::getInstance().getFrameNumInSec());

		// 入力テスト
		DrawFormatString(0, 30, red, "Left: %d", InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT));
		DrawFormatString(0, 60, red, "Right: %d", InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT));
		DrawFormatString(0, 90, red, "Up: %d", InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN));
		DrawFormatString(0, 120, red, "Down: %d", InputManager::getInstance().checkPushFrame(KEY_INPUT_UP));
#endif
	}

}
