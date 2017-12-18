#include "PlayerState.h"

#include "InputManager.h"
#include "GameSceneParam.h"
#include "DxLib.h"
#include <cmath>
#include "GraphManager.h"
#include "GlobalParam.h"
#include <string>


const std::string PLAYER_DIR_NAME = std::string(GRAPH_DIR_PATH) + "Player/";


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
void PlayerStandState::Enter(Player* player){
	mAnimFrame = 0;
	char dir[4] = {GameObj::DIRECTON_UP, GameObj::DIRECTON_DOWN, GameObj::DIRECTON_RIGHT, GameObj::DIRECTON_LEFT};
	for(int d = 0; d < 4; d++){
		for(int i = 0;; i++){
			int id = GraphManager::getInstance().getDerivGraph(PLAYER_DIR_NAME + GRAPH_NAME + dir[d] + ".png", i, GameSceneParam::MASS_SIZE);
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

	// 移動入力を検知したら歩きステートに変える
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


// ------PlayerWalkStateクラスの実装------
void PlayerWalkState::Enter(Player* player){
	mAnimFrame = 0;
	char dir[4] = {GameObj::DIRECTON_UP, GameObj::DIRECTON_DOWN, GameObj::DIRECTON_RIGHT, GameObj::DIRECTON_LEFT};
	for(int d = 0; d < 4; d++){
		for(int i = 0;; i++){
			int id = GraphManager::getInstance().getDerivGraph(PLAYER_DIR_NAME + GRAPH_NAME + dir[d] + ".png", i, GameSceneParam::MASS_SIZE);
			if(id == -1){ break; }
			mKeepGraph[dir[d]].push_back(id);
		}
	}
	player->changeGraphic(mKeepGraph[player->checkDirection()][0]);
}

void PlayerWalkState::Execute(Player* player){

	// 加算する速度と向きを計算
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

	// アニメーション遷移
	mAnimFrame++;
	if( (mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK) >= mKeepGraph[player->checkDirection()].size()){ mAnimFrame = 0; }
	player->changeGraphic(mKeepGraph[player->checkDirection()][mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK]);

	// 待機ステートに移行
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


// ------PlayerHoldStateクラスの実装------
void PlayerHoldState::Enter(Player* player){

	mAnimFrame = 0;
	for(int i = 0;; i++){
		int id = GraphManager::getInstance().getDerivGraph(PLAYER_DIR_NAME + GRAPH_NAME + player->checkDirection() + ".png", i, GameSceneParam::MASS_SIZE);
		if(id == -1){ break; }
		mKeepGraph.push_back(id);
	}
	player->changeGraphic(mKeepGraph[0]);

	// あたり判定をつかんだマスに沿って変える
	HitArea diffHitArea;
	diffHitArea.center = Vec2D<int>(0, 0);
	diffHitArea.size = Vec2D<int>(0, 0);
	switch(player->checkDirection()){
		case GameObj::DIRECTON_UP:
			diffHitArea.size.y += GameSceneParam::MASS_SIZE;
			diffHitArea.center.y -= GameSceneParam::MASS_SIZE / 2;
			break;
		case GameObj::DIRECTON_DOWN:
			diffHitArea.size.y += GameSceneParam::MASS_SIZE;
			diffHitArea.center.y += GameSceneParam::MASS_SIZE / 2;
			break;
		case GameObj::DIRECTON_RIGHT:
			diffHitArea.size.x += GameSceneParam::MASS_SIZE;
			diffHitArea.center.x += GameSceneParam::MASS_SIZE / 2;
			break;
		case GameObj::DIRECTON_LEFT:
			diffHitArea.size.x += GameSceneParam::MASS_SIZE;
			diffHitArea.center.x -= GameSceneParam::MASS_SIZE / 2;
	}
	player->changeHitAreaCenter(diffHitArea.center);
	player->changeHitAreaSize(player->checkHitArea().size + diffHitArea.size);

	// 掴んだマスのあたり判定を一時的に消す
	mMass->changeHitAreaSize(Vec2D<int>(0, 0));
}

// アニメーションは半分進んだ時点で「掴んだ」モーションになることに注意
void PlayerHoldState::Execute(Player* player){

	if(mAnimFrame < (mKeepGraph.size() / 2) * GameSceneParam::ANIME_CHANGE_FRAME_QUICK){	// 掴む前
		mAnimFrame++;
		mPreviousPlayerPos = player->checkPos();
	}
	else if(mAnimFrame > (mKeepGraph.size() / 2) * GameSceneParam::ANIME_CHANGE_FRAME_QUICK){	// 離す時
		mAnimFrame++;
		if((mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK) >= mKeepGraph.size()){
			player->getStateMachine()->changeState(new PlayerStandState());
			return;
		}
	}
	else{	// 掴んでいるとき
	
		holdAction(player);

		// 決定キーで掴むのを止める
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1){
			mAnimFrame++;
		}
	}

	player->changeGraphic(mKeepGraph[mAnimFrame / GameSceneParam::ANIME_CHANGE_FRAME_QUICK]);
}

void PlayerHoldState::Exit(Player* player){

	// あたり判定を元に戻す
	player->changeHitAreaCenter(Vec2D<int>(0, 0));
	player->changeHitAreaSize(Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE));
	mMass->changeHitAreaSize(Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE));

	for(int id : mKeepGraph){
		DeleteGraph(id);
	}
}

void PlayerHoldState::holdAction(Player* player){

	// 加算する速度と向きを計算
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

	// 掴んでいるオブジェクトをプレイヤーに合わせて動かす
	mMass->movePos(player->checkPos() - mPreviousPlayerPos);
	mPreviousPlayerPos = player->checkPos();
	
}


// ------PlayerItemGetStateクラスの実装------
void PlayerItemGetState::Enter(Player* player){

	mAnimFrame = 0;
	for(int i = 0;; i++){
		int id = GraphManager::getInstance().getDerivGraph(PLAYER_DIR_NAME + GRAPH_NAME + ".png", i, GameSceneParam::MASS_SIZE);
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
