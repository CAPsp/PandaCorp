#pragma once


#include "BaseScene.h"
#include "StageControll.h"
#include "StageEndProcess.h"
#include "ItemStock.h"


class GameScene : public BaseScene{

public:
	GameScene(int){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();
	void uiDraw();	// UIを描画する処理

// ステージ終了をしたいときに呼ばれる静的関数群
public:
	static void toGameOver(){ sEndProcess.gameover(); }
	static void toClear(){ sEndProcess.clear(); }
	static void toStageSelect(){ sEndProcess.returnStageSelect(); }

private:
	StageControll* mStage;
	static StageEndProcess sEndProcess;
	int mStageNameFontHandle;
	std::pair<int, int> mDate;	// ゲーム内の日付
	int mProgressFrame = 0;		// ゲーム開始から経過したフレーム
	ItemStock mItemStock;

};