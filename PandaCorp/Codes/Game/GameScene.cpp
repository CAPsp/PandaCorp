#include "GameScene.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "GameSceneParam.h"


StageEndProcess GameScene::sEndProcess;


bool GameScene::begin(){
	sEndProcess.init();
	return true;
}


scene_sig GameScene::update(){

	mStage.update();

#ifdef _DEBUG
	// UIの枠を表示
	int frameColor = GetColor(255, 0, 0);
	DrawBox(0,	 0,	920,						GlobalParam::WINDOW_SIZE.y, frameColor, false);
	DrawBox(920, 0,	GlobalParam::WINDOW_SIZE.x,	GlobalParam::WINDOW_SIZE.y, frameColor, false);

	int massColor = GetColor(0, 255, 0);
	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		for(int x = 0; x < GameSceneParam::MASS_NUM.x; x++){
			DrawBox( x * GameSceneParam::MASS_SIZE, y * GameSceneParam::MASS_SIZE,
					 (x + 1) * GameSceneParam::MASS_SIZE, (y + 1) * GameSceneParam::MASS_SIZE,
					 massColor, false);
		}
	}
#endif

	return sEndProcess.update();	// ゲームオーバーやクリア処理をしてないときはシーンを切り替えないようにしてる
}


bool GameScene::end(){
	return true;
}