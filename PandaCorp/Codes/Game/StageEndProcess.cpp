#include "StageEndProcess.h"
#include "DxLib.h"
#include "GlobalParam.h"


void procGameover(scene_sig&);
void procClear(scene_sig&);
void procReturnStageSelect(scene_sig&);


scene_sig StageEndProcess::update(){

	scene_sig rtn;
	rtn.next = scene_id::NONE;

	switch(mCurrentState){
		case GAME_OVER:
			procGameover(rtn);
			break;

		case CLEAR:
			procClear(rtn);
			break;

		case RETURN_SELECT:
			procReturnStageSelect(rtn);

	}

	return rtn;
}


// 画面にエフェクトをかけ、リトライかステージ選択に戻るかを選ばせる
void procGameover(scene_sig& signal){

	static int effectPal = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, effectPal);
	DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(255, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	effectPal += 2;
	if(effectPal >= 255){
		effectPal = 255;

		// 選択肢ウィンドウの表示
		signal.next = STAGE_SELECT;

	}

}


// クリア時のスコアを表示し、次に進むかステージ選択に戻るかを選ばせる
void procClear(scene_sig& signal){

	static int effectPal = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, effectPal);
	DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	effectPal += 2;
	if(effectPal >= 255){
		effectPal = 255;

		// 選択肢ウィンドウの表示
		signal.next = STAGE_SELECT;

	}
	
}


// 本当に戻るかどうかを確認した後にとどまるかステージ選択に戻るかを決める
void procReturnStageSelect(scene_sig&){}
