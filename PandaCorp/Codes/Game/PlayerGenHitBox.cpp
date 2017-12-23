#include "PlayerGenHitBox.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Mass.h"
#include "PlayerState.h"


PlayerGenHitBox::PlayerGenHitBox(GameObjContainer* ow, Player* p)
	:mPlayer(p), GameObj(ow, Vec2D<int>(), HitArea{}){

	// プレイヤーの前方に置く
	Vec2D<int> pos = mPlayer->checkPos();
	switch(mPlayer->checkDirection()){
		case GameObj::DIRECTON_UP:
			pos.y -= GameSceneParam::MASS_SIZE;
			break;
		case GameObj::DIRECTON_DOWN:
			pos.y += GameSceneParam::MASS_SIZE;
			break;
		case GameObj::DIRECTON_LEFT:
			pos.x -= GameSceneParam::MASS_SIZE;
			break;
		case GameObj::DIRECTON_RIGHT:
			pos.x += GameSceneParam::MASS_SIZE;
			break;
	}
	mPos = pos;

	mHitArea.size = Vec2D<int>(GameSceneParam::MASS_SIZE / 4, GameSceneParam::MASS_SIZE / 4);
}


void PlayerGenHitBox::update(){

	static bool flag = false;

	if(flag){
		mOwner->remove(this);
	}

	flag = !flag;
}


void PlayerGenHitBox::draw(){
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y - (mHitArea.size.y / 2) + mHitArea.center.y,
			mPos.x + (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y + (mHitArea.size.y / 2) + mHitArea.center.y,
			GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif
}


void PlayerGenHitBox::hit(GameObj* other){

	
	// 掴めるものがあったら掴む
	Mass* tmp = dynamic_cast<Mass*>(other);
	if(tmp != NULL && tmp->isObstacle()){
		mPlayer->getStateMachine()->changeState(new PlayerHoldState(tmp));
	}

	// アイテム取得
	/*
	if(tmp != NULL && !tmp->isPass()){
		mPlayer->getStateMachine()->changeState(new PlayerItemGetState());
	}
	*/

}