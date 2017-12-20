//
// シーン遷移処理を担う
//

#pragma once


#include "BaseScene.h"


class ChangeSceneManager{

public:
	ChangeSceneManager(BaseScene** scene, scene_sig sig) :
		mScene(scene),
		mSignal(sig){}
	bool update();

private:
	BaseScene** mScene = nullptr;	// 現在処理しているシーン(MainControllクラスから引き継いだもの)
	scene_sig mSignal;				// 前シーンからわたされた信号
	bool mIsEndBefore = false;		// 前シーンの終了処理が終わったかどうか

};