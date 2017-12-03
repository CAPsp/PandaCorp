#include "Player.h"

#include "DxLib.h"
#include "GameSceneParam.h"
#include <string>
#include "InputManager.h"


Player::Player(){

	// TODO: デバッグ用
	for(int i = 0; i < 4; i++){
		std::string path = "Res/Graph/Chara/chara" + std::to_string(i) + ".png";
		LoadDivGraph(path.c_str(), 4, 4, 1, GameSceneParam::MASS_SIZE, (int)((double)GameSceneParam::MASS_SIZE * 1.5), mAnimGID[i]);
	}
	mPos = {100, 100};

}


Player::~Player(){
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 4; x++){
			DeleteGraph(mAnimGID[y][x]);
		}
	}
}


void Player::update(){

	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0){
		mDir = chara_dir::U;
		mPos.y -= 4;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0){
		mDir = chara_dir::R;
		mPos.x += 4;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0){
		mDir = chara_dir::D;
		mPos.y += 4;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0){
		mDir = chara_dir::L;
		mPos.x -= 4;
	}

	// 描画
	DrawGraph(mPos.x, mPos.y, mAnimGID[mDir][mNowAnimElem], true);

	// TODO: アニメを送る処理
	static int animFlowCnt = 0;
	animFlowCnt++;
	if(animFlowCnt > 20){
		animFlowCnt = 0;
		mNowAnimElem++;
		if(mNowAnimElem >= 4){
			mNowAnimElem = 0;
		}
	}

}