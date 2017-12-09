//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include <vector>
#include "Mass.h"
#include "GameObj.h"
#include "StageFile.h"


class StageControll{

public:
	StageControll(std::string);		// 読み込むjsonファイルを指定する
	~StageControll();
	void update();					// 1フレーム毎の更新処理

private:
	std::vector<GameObj*> mObjects;
	std::vector<Mass*> mMasses;
	StageFile mStageFile;

};