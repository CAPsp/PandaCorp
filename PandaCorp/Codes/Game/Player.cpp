#include "Player.h"

#include "DxLib.h"
#include "GameSceneParam.h"
#include "InputManager.h"
#include "Mass.h"
#include "PlayerState.h"
#include "PlayerGenHitBox.h"
#include "DebugMsgData.h"


Player::Player(GameObjContainer* ow, Vec2D<int> pos)
	:GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}){

	mVel = Vec2D<double>(0, 0);
	mStateMachine = new StateMachine<Player>(this, new PlayerStandState(), new PlayerGlobalState());
}


Player::~Player(){}


void Player::update(){
	mStateMachine->update();
}


void Player::draw(){

	Vec2D<int> gSize;
	GetGraphSize(mCurrentGID, &gSize.x, &gSize.y);
	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
				  mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
				  1.0, 0, mCurrentGID, true);

#ifdef _DEBUG

	DebugMsgData::getInstance().setMsg("PlayerV", std::string("V = ") + std::to_string(mVel.x) + " : " + std::to_string(mVel.y));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y - (mHitArea.size.y / 2) + mHitArea.center.y,
			mPos.x + (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y + (mHitArea.size.y / 2) + mHitArea.center.y,
			GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif

}


void Player::hit(GameObj* other){

	// マスとの衝突を判定
	Mass* tmp = dynamic_cast<Mass*>(other);
	if(tmp != NULL){

		if(!tmp->isPass()){

			// どのくらい重なっているのかを計算
			Vec2D<int> p = mPos + mHitArea.center;
			Vec2D<int> q = other->checkPos() + other->checkHitArea().center;
			int dx;
			if(p.x <= q.x){
				dx = (p.x + mHitArea.size.x / 2) - (q.x - other->checkHitArea().size.x / 2);
				dx *= (-1);
			}
			else{
				dx = (q.x + other->checkHitArea().size.x / 2) - (p.x - mHitArea.size.x / 2);
			}

			int dy;
			if(p.y <= q.y){
				dy = (p.y + mHitArea.size.y / 2) - (q.y - other->checkHitArea().size.y / 2);
				dy *= (-1);
			}
			else{
				dy = (q.y + other->checkHitArea().size.y / 2) - (p.y - mHitArea.size.y / 2);
			}

			// 移動距離が少ない方に動いて重なりを外す
			// マスのつなぎ目で動けなくなるバグをなくすために比較演算子をランダムに変更する
			static bool flag;
			flag = GetRand(1);
			if( (flag && abs(dy) >= abs(dx)) || (!flag && abs(dy) > abs(dx)) ){
				mPos.x += dx;
			}
			else{
				mPos.y += dy;
			}

		}
		return;
	}

}

void Player::genHitBox(){
	mOwner->add(new PlayerGenHitBox(mOwner, this));
}