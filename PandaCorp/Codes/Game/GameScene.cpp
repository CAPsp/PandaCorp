#include "GameScene.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "GameSceneParam.h"


bool GameScene::begin(){
	return true;
}


scene_sig GameScene::update(){
	scene_sig rtn;

	mStage.draw();

#ifdef _DEBUG
	// UI‚Ì˜g‚ð•\Ž¦
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

	rtn.next = scene_id::NONE;
	return rtn;
}


bool GameScene::end(){
	return true;
}