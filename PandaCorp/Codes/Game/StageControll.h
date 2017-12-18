//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include "StageFile.h"
#include "GameObjContainer.h"
#include "GameSceneParam.h"


class StageControll{

public:
	StageControll(std::string);		// 読み込むjsonファイルを指定する
	~StageControll();
	void update();					// 1フレーム毎の更新処理

private:
	GameObjContainer mObjects[2];	// マス + 他ゲームオブジェクト
	StageFile mStageFile;

};