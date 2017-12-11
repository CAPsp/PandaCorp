//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include <vector>
#include "GameObj.h"
#include "StageFile.h"
#include "GameObjContainer.h"


class StageControll{

public:
	StageControll(std::string);		// 読み込むjsonファイルを指定する
	~StageControll();
	void update();					// 1フレーム毎の更新処理

private:
	GameObjContainer mObjects;
	GameObjContainer mMasses;
	StageFile mStageFile;

};