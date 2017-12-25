#include "TitleScene.h"

#include "SoundManager.h"
#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "InputManager.h"


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
	DrawBox(0, 0, GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y, GetColor(0, 255, 0), true);

	// タイトル
	int w;
	std::string str = "ぱんだつ！";
	w = GetDrawStringWidth(str.c_str(), (int)strlen(str.c_str()));
	DrawString(GlobalParam::WINDOW_SIZE.x / 2 - w / 2, 200, str.c_str(), GetColor(255, 0, 0));

	// スタート
	str = "出社する";
	w = GetDrawStringWidth(str.c_str(), (int)strlen(str.c_str()));
	DrawString(GlobalParam::WINDOW_SIZE.x / 2 - w / 2, 500, str.c_str(), GetColor(255, 0, 0));

	// エンド
	str = "今日は休む";
	w = GetDrawStringWidth(str.c_str(), (int)strlen(str.c_str()));
	DrawString(GlobalParam::WINDOW_SIZE.x / 2 - w / 2, 600, str.c_str(), GetColor(255, 0, 0));

	int baseY = (mIsSelectedStart) ? 500 : 600;
	DrawBox(GlobalParam::WINDOW_SIZE.x / 4,		baseY,
			GlobalParam::WINDOW_SIZE.x / 4 * 3, baseY + 20,
			GetColor(255, 255, 0), false);

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