#include "PlayerState.h"

#include "InputManager.h"
#include "GameSceneParam.h"
#include "DxLib.h"
#include <cmath>


// ------PlayerGlobalStateクラスの実装------
void PlayerGlobalState::Execute(Player* player){

	// 現在の速度の反映
	Vec2D<double> currentVel = player->checkVelocity();
	player->movePos(Vec2D<int>((int)currentVel.x, (int)currentVel.y));

	// 速度減退処理
	Vec2D<double> addVel;
	if(currentVel.x != 0.0){
		addVel.x = (-1.0) * ((currentVel.x) / (abs(currentVel.x))) * (abs(currentVel.x) * GameSceneParam::PLAYER_VEL_RESISTANCE);
	}
	if(currentVel.y != 0.0){
		addVel.y = (-1.0) * ((currentVel.y) / (abs(currentVel.y))) * (abs(currentVel.y) * GameSceneParam::PLAYER_VEL_RESISTANCE);
	}
	player->addVelocity(addVel);

}


// ------PlayerStandStateクラスの実装------
void PlayerStandState::Enter(Player* player){}

void PlayerStandState::Execute(Player* player){

	// 移動入力を検知したら歩きステートに変える
	if( (InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0)		||
		(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0))	{

		player->getStateMachine()->changeState(new PlayerWalkState());
	}
}

void PlayerStandState::Exit(Player* player){}


// ------PlayerWalkStateクラスの実装------
void PlayerWalkState::Enter(Player* player){}

void PlayerWalkState::Execute(Player* player){

	// 加算する速度を計算
	Vec2D<double> addVel;
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0){
		addVel.y = (-1.0) * GameSceneParam::PLAYER_ACCELE_PER_FRAME;
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0){
		addVel.x = GameSceneParam::PLAYER_ACCELE_PER_FRAME;
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0){
		addVel.y = GameSceneParam::PLAYER_ACCELE_PER_FRAME;
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0){
		addVel.x = (-1.0) * GameSceneParam::PLAYER_ACCELE_PER_FRAME;
	}

	// 最高速度を超えないように加算する速度を調整
	Vec2D<double> currentVel = player->checkVelocity();
	if(abs(addVel.x + currentVel.x) > GameSceneParam::PLAYER_MAX_SPEED){
		addVel.x = GameSceneParam::PLAYER_MAX_SPEED - abs(currentVel.x);
		addVel.x *= currentVel.x / abs(currentVel.x);
	}
	if(abs(addVel.y + currentVel.y) > GameSceneParam::PLAYER_MAX_SPEED){
		addVel.y = GameSceneParam::PLAYER_MAX_SPEED - abs(currentVel.y);
		addVel.y *= currentVel.y / abs(currentVel.y);
	}

	player->addVelocity(addVel);

	// 待機ステートに移行
	if(addVel.x == 0.0 && addVel.y == 0.0){
		player->getStateMachine()->changeState(new PlayerStandState());
	}
}

void PlayerWalkState::Exit(Player* player){}


// ------PlayerHoldStateクラスの実装------
void PlayerHoldState::Enter(Player* player){}

void PlayerHoldState::Execute(Player* player){


}

void PlayerHoldState::Exit(Player* player){}



// ------PlayerItemGetStateクラスの実装------
void PlayerItemGetState::Enter(Player* player){}

void PlayerItemGetState::Execute(Player* player){


}

void PlayerItemGetState::Exit(Player* player){}
