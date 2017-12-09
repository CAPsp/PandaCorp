#include "Player.h"

#include "DxLib.h"
#include "GameSceneParam.h"
#include "InputManager.h"


Player::Player(int x, int y){

	mPos.x = x;
	mPos.y = y;
	mHitAreaSize = Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE);
}


Player::~Player(){}


void Player::update(){

	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0){
		mPos.y -= GameSceneParam::PLAYER_SPEED_PIXEL_PER_FRAME;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0){
		mPos.x += GameSceneParam::PLAYER_SPEED_PIXEL_PER_FRAME;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0){
		mPos.y += GameSceneParam::PLAYER_SPEED_PIXEL_PER_FRAME;
	}
	else if(InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0){
		mPos.x -= GameSceneParam::PLAYER_SPEED_PIXEL_PER_FRAME;
	}

	// •`‰æ
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitAreaSize.x / 2),
			mPos.y - (mHitAreaSize.y / 2),
			mPos.x + (mHitAreaSize.x / 2),
			mPos.y + (mHitAreaSize.y / 2), GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif

}


void Player::hit(GameObj& other){

}