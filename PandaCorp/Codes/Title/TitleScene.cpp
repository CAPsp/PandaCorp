#include "TitleScene.h"

#include "SoundManager.h"
#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "InputManager.h"
#include "GraphManager.h"

#define _USE_MATH_DEFINES
#include <math.h>



bool TitleScene::begin(){
	PlaySoundMem(SoundManager::getInstance().checkID("BGM/title01.ogg"), DX_PLAYTYPE_BACK);
	return true;
}


scene_sig TitleScene::update(){

	scene_sig signal;

	draw();

	// 終了処理中
	if(mIsEnded){

		if(mFeedPal >= 255){

			if(mIsSelectedStart){
				signal.next = scene_id::STAGE_SELECT;
			}
			else{
				signal.next = scene_id::END;
			}
		}
	}
	else{

		// ESCキーが押されたら終了する
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_ESCAPE) == 1){
			mIsSelectedStart = false;
			PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			mIsEnded = true;
		}

		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) == 1 ||
		   InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) == 1){

			mIsSelectedStart = !mIsSelectedStart;
			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}

		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1){

			PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			mIsEnded = true;
		}
	}

	return signal;
}


void TitleScene::draw(){
	
	// 背景
	DrawGraph(0, 0, GraphManager::getInstance().checkID(std::string(GRAPH_DIR_PATH) + "UI/others/title_back.png", Vec2D<int>(0, 0)), false);

	// スタート
	DrawRotaGraph(GlobalParam::WINDOW_SIZE.x / 2, 500, 1.0, 0.0,
				  GraphManager::getInstance().checkID(std::string(GRAPH_DIR_PATH) + "UI/others/title_start.png", Vec2D<int>(0, 0)),
				  true, false);

	// エンド
	DrawRotaGraph(GlobalParam::WINDOW_SIZE.x / 2, 600, 1.0, 0.0,
				  GraphManager::getInstance().checkID(std::string(GRAPH_DIR_PATH) + "UI/others/title_end.png", Vec2D<int>(0, 0)),
				  true, false);

	// カーソル
	static double deg = 0.0;
	deg += (deg + 4.0 >= 360.0) ? (-360.0 + 4.0) : 4.0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)((sin(deg * M_PI / 180.0) + 1.0) * 127.0));

	int baseY = (mIsSelectedStart) ? 500 : 600;
	std::string fileCursor = std::string(GRAPH_DIR_PATH) + "UI/others/" + ((mIsSelectedStart) ? "title_select_frame_small.png" : "title_select_frame_big.png");
	DrawRotaGraph(GlobalParam::WINDOW_SIZE.x / 2, baseY, 1.0, 0.0,
				  GraphManager::getInstance().checkID(fileCursor, Vec2D<int>(0, 0)),
				  true, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 終了処理中は暗転する
	if(mIsEnded){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFeedPal);
		DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		mFeedPal += 5;
	}
}


bool TitleScene::end(){
	StopSoundMem(SoundManager::getInstance().checkID("BGM/title01.ogg"));
	return true;
}