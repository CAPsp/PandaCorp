#include "ChangeSceneManager.h"

#include "DebugMsgData.h"

#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"


// return: 
//	true = 遷移処理が終わったことを示す
//	false = 遷移処理が終わっていない
bool ChangeSceneManager::update(){

	// 前シーンの終了処理
	if(!mIsEndBefore){

		// 終了処理が終わったら次のシーンのインスタンスを生成
		if((*mScene)->end()){

			// シーン切り替え時にデバッグメッセージを初期化する
			DebugMsgData::getInstance().deleteData();

			delete *mScene;
			*mScene = nullptr;
			
			switch(mSignal.next){

				case scene_id::TITLE:
					*mScene = new TitleScene();
					break;

				case scene_id::STAGE_SELECT:
					*mScene = new StageSelectScene();
					break;

				case scene_id::GAME:
					*mScene = new GameScene(mSignal.meta);
					break;

				default:
					// TODO: 例外発生処理
					break;

			}

			mIsEndBefore = true;
		}
	}

	//  次シーンの開始処理
	return (*mScene)->begin();
}