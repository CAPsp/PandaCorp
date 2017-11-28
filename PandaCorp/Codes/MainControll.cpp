#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"
#include "InputManager.h"
#include "DebugMsgData.h"
#include "GlobalParam.h"

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
		std::vector<std::string> debugMsg = DebugMsgData::getInstance().getAllMsg();
		for(int i = 0; i < debugMsg.size(); i++){
			DrawString(0, i * GlobalParam::FONT_SIZE, debugMsg[i].c_str(), GetColor(255, 0, 0));
		}
#endif
	}

}
