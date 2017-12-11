#include "PlayerState.h"

#include "InputManager.h"
#include "GameSceneParam.h"
#include "DxLib.h"
#include <cmath>
#include "GraphManager.h"
#include "GlobalParam.h"
#include <string>


const std::string PLAYER_DIR_NAME = std::string(GRAPH_DIR_PATH) + "Player/";

// �摜����n���ꂽ�A�j���[�V�������ɉ������̈�𔲂��o���A�V���ȃO���t�B�b�N�n���h���Ƃ��Đ�������
// �����o���Ȃ��ꍇ-1���Ԃ�
int genAnimGraph(std::string fileName, int& num){
	int id = GraphManager::getInstance().checkID(PLAYER_DIR_NAME + fileName);
	if(id == -1){ return -1; }
	
	int width, height;
	GetGraphSize(id, &width, &height);
	id = DerivationGraph(GameSceneParam::MASS_SIZE * num, 0, GameSceneParam::MASS_SIZE, height, id);

	return id;
}


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
void PlayerStandState::Enter(Player* player){
	mAnimFrame = 0;
	char dir[4] = {GameObj::DIRECTON_UP, GameObj::DIRECTON_DOWN, GameObj::DIRECTON_RIGHT, GameObj::DIRECTON_LEFT};
	for(int d = 0; d < 4; d++){
		for(int i = 0;; i++){
			int id = genAnimGraph(GRAPH_NAME + dir[d] + ".png", i);
			if(id == -1){ break; }
			mKeepGraph[dir[d]].push_back(id);
		}
	}
	player->changeGraphic(mKeepGraph[player->checkDirection()][0]);
}

void PlayerStandState::Execute(Player* player){

	mAnimFrame++;
	if( (mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL) >= mKeepGraph[player->checkDirection()].size()){ mAnimFrame = 0; }
	player->changeGraphic(mKeepGraph[player->checkDirection()][mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_NORMAL]);

	// �ړ����͂����m����������X�e�[�g�ɕς���
	if( (InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0)		||
		(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0)	||
	    (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0))	{

		player->getStateMachine()->changeState(new PlayerWalkState());
	}

	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1){
		player->genHitBox();
	}
}

void PlayerStandState::Exit(Player*){
	for(auto itr = mKeepGraph.begin(); itr != mKeepGraph.end(); itr++){
		for(int id : itr->second){
			DeleteGraph(id);
		}
	}
}


// ------PlayerWalkState�N���X�̎���------
void PlayerWalkState::Enter(Player* player){
	mAnimFrame = 0;
	char dir[4] = {GameObj::DIRECTON_UP, GameObj::DIRECTON_DOWN, GameObj::DIRECTON_RIGHT, GameObj::DIRECTON_LEFT};
	for(int d = 0; d < 4; d++){
		for(int i = 0;; i++){
			int id = genAnimGraph(GRAPH_NAME + dir[d] + ".png", i);
			if(id == -1){ break; }
			mKeepGraph[dir[d]].push_back(id);
		}
	}
	player->changeGraphic(mKeepGraph[player->checkDirection()][0]);
}

void PlayerWalkState::Execute(Player* player){

	// ���Z���鑬�x�ƌ������v�Z
	Vec2D<double> addVel;
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) > 0){
		addVel.y = (-1.0) * GameSceneParam::PLAYER_ACCELE_PER_FRAME;
		player->changeDirection(GameObj::DIRECTON_UP);
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) > 0){
		addVel.x = GameSceneParam::PLAYER_ACCELE_PER_FRAME;
		player->changeDirection(GameObj::DIRECTON_RIGHT);
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) > 0){
		addVel.y = GameSceneParam::PLAYER_ACCELE_PER_FRAME;
		player->changeDirection(GameObj::DIRECTON_DOWN);
	}
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) > 0){
		addVel.x = (-1.0) * GameSceneParam::PLAYER_ACCELE_PER_FRAME;
		player->changeDirection(GameObj::DIRECTON_LEFT);
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

	// �A�j���[�V�����J��
	mAnimFrame++;
	if( (mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK) >= mKeepGraph[player->checkDirection()].size()){ mAnimFrame = 0; }
	player->changeGraphic(mKeepGraph[player->checkDirection()][mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK]);

	// �ҋ@�X�e�[�g�Ɉڍs
	if(addVel.x == 0.0 && addVel.y == 0.0){
		player->getStateMachine()->changeState(new PlayerStandState());
	}
}

void PlayerWalkState::Exit(Player*){
	for(auto itr = mKeepGraph.begin(); itr != mKeepGraph.end(); itr++){
		for(int id : itr->second){
			DeleteGraph(id);
		}
	}
}


// ------PlayerHoldState�N���X�̎���------
void PlayerHoldState::Enter(Player* player){

	mAnimFrame = 0;
	for(int i = 0;; i++){
		int id = genAnimGraph(GRAPH_NAME + player->checkDirection() + ".png", i);
		if(id == -1){ break; }
		mKeepGraph.push_back(id);
	}
	player->changeGraphic(mKeepGraph[0]);

	mPreviousPlayerPos = player->checkPos();
}

// �A�j���[�V�����͔����i�񂾎��_�Łu�͂񂾁v���[�V�����ɂȂ邱�Ƃɒ���
void PlayerHoldState::Execute(Player* player){

	if(mAnimFrame < (mKeepGraph.size() / 2) * GameSceneParam::ANIME_CHANGE_FRAME_QUICK){	// �͂ޑO
		mAnimFrame++;
		
	}
	else if(mAnimFrame > (mKeepGraph.size() / 2) * GameSceneParam::ANIME_CHANGE_FRAME_QUICK){	// ������
		mAnimFrame++;
		if((mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK) >= mKeepGraph.size()){
			player->getStateMachine()->changeState(new PlayerStandState());
			return;
		}
	}
	else{	// �͂�ł���Ƃ�
	
		holdAction(player);

		// ����L�[�Œ͂ނ̂��~�߂�
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1){
			mAnimFrame++;
		}
	}

	player->changeGraphic(mKeepGraph[mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK]);
}

void PlayerHoldState::Exit(Player*){
	for(int id : mKeepGraph){
		DeleteGraph(id);
	}
}

void PlayerHoldState::holdAction(Player* player){

	// ���Z���鑬�x�ƌ������v�Z
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

	// �͂�ł���I�u�W�F�N�g���v���C���[�ɍ��킹�ē�����
	Vec2D<int> diff = player->checkPos() - mPreviousPlayerPos;
	mMass->movePos(diff);
	mPreviousPlayerPos = player->checkPos();
}


// ------PlayerItemGetState�N���X�̎���------
void PlayerItemGetState::Enter(Player* player){

	mAnimFrame = 0;
	for(int i = 0;; i++){
		int id = genAnimGraph(GRAPH_NAME + ".png", i);
		if(id == -1){ break; }
		mKeepGraph.push_back(id);
	}
	player->changeGraphic(mKeepGraph[0]);
}

void PlayerItemGetState::Execute(Player* player){
	mAnimFrame++;
	if((mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK) >= mKeepGraph.size()){
		player->getStateMachine()->changeState(new PlayerStandState());
		return;
	}
	player->changeGraphic(mKeepGraph[mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK]);

}

void PlayerItemGetState::Exit(Player*){
	for(int id : mKeepGraph){
		DeleteGraph(id);
	}
}
