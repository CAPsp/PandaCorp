#include "MainControll.h"

#include "DxLib.h"
#include "FPSManager.h"


// ゲームのメインループ処理
void MainControll::doMainLoop(){

	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){

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
		// 左上に現在のFPSを表示
		DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", FPSManager::getInstance().getFrameNumInSec());
#endif
	}

}
