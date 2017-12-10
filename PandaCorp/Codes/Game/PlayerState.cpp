#include "PlayerState.h"

#include "InputManager.h"
#include "GameSceneParam.h"
#include "DxLib.h"
#include <cmath>


// ------PlayerGlobalState�N���X�̎���------
void PlayerGlobalState::Execute(Player* player){

	// ���݂̑��x�̔��f
	Vec2D<double> currentVel = player->checkVelocity();
	player->movePos(Vec2D<int>((int)currentVel.x, (int)currentVel.y));

	// ���x���ޏ���
	Vec2D<double> addVel;
	if(currentVel.x != 0.0){
		addVel.x = (-1.0) * ((currentVel.x) / (abs(currentVel.x))) * (abs(currentVel.x) * GameSceneParam::PLAYER_VEL_RESISTANCE);
	}
	if(currentVel.y != 0.0){
		addVel.y = (-1.0) * ((currentVel.y) / (abs(currentVel.y))) * (abs(currentVel.y) * GameSceneParam::PLAYER_VEL_RESISTANCE);
	}
	player->addVelocity(addVel);

}


// ------PlayerStandState�N���X�̎���------
void PlayerStandState::Enter(Player* player){}

void PlayerStandState::Execute(Player* player){

	// �ړ����͂����m����������X�e�[�g�ɕς���
	if( (InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0)		||
		(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0))	{

		player->getStateMachine()->changeState(new PlayerWalkState());
	}
}

void PlayerStandState::Exit(Player* player){}


// ------PlayerWalkState�N���X�̎���------
void PlayerWalkState::Enter(Player* player){}

void PlayerWalkState::Execute(Player* player){

	// ���Z���鑬�x���v�Z
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

	// �ō����x�𒴂��Ȃ��悤�ɉ��Z���鑬�x�𒲐�
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

	// �ҋ@�X�e�[�g�Ɉڍs
	if(addVel.x == 0.0 && addVel.y == 0.0){
		player->getStateMachine()->changeState(new PlayerStandState());
	}
}

void PlayerWalkState::Exit(Player* player){}


// ------PlayerHoldState�N���X�̎���------
void PlayerHoldState::Enter(Player* player){}

void PlayerHoldState::Execute(Player* player){


}

void PlayerHoldState::Exit(Player* player){}



// ------PlayerItemGetState�N���X�̎���------
void PlayerItemGetState::Enter(Player* player){}

void PlayerItemGetState::Execute(Player* player){


}

void PlayerItemGetState::Exit(Player* player){}
