#include "PlayerGenHitBox.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Mass.h"
#include "PlayerState.h"


PlayerGenHitBox::PlayerGenHitBox(GameObjContainer* ow, Player* p)
	:mPlayer(p), GameObj(ow, Vec2D<int>(), Vec2D<int>()){

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

	mHitAreaSize = Vec2D<int>(GameSceneParam::MASS_SIZE / 4, GameSceneParam::MASS_SIZE / 4);
}


void PlayerGenHitBox::update(){

	static bool flag = false;

	if(flag){
		mOwner->remove(this);
	}

	flag = !flag;
}


void PlayerGenHitBox::draw(int){
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitAreaSize.x / 2),
			mPos.y - (mHitAreaSize.y / 2),
			mPos.x + (mHitAreaSize.x / 2),
			mPos.y + (mHitAreaSize.y / 2), GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif
}


void PlayerGenHitBox::hit(GameObj* other){

	Mass* tmp = dynamic_cast<Mass*>(other);
	if(tmp != NULL && !tmp->isPass()){
		mPlayer->getStateMachine()->changeState(new PlayerItemGetState());
	}

}