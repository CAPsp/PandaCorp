//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include "StageFile.h"
#include "GameObjContainer.h"
#include "GameSceneParam.h"
#include "ItemStock.h"


class StageControll{

public:
	StageControll(std::string);					// 読み込むjsonファイルを指定する
	~StageControll();
	void update();								// 1フレーム毎の更新処理
	void checkExistClearMass(const ItemStock&);	// 触れたらクリアできるマスがあるかどうかの確認

private:
	GameObjContainer mObjects[2];	// マス + 他ゲームオブジェクト
	StageFile mStageFile;
	int mHighScore;

};