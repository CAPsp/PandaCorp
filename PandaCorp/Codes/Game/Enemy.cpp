#include "Enemy.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "EnemyState.h"
#include "Mass.h"
#include "Player.h"


Enemy::Enemy(GameObjContainer* ow, std::vector<Vec2D<int>> patrolVec)
	:GameObj(ow, patrolVec[0], HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}),
	mPatrolPoint(patrolVec){

	mStateMachine = new StateMachine<Enemy>(this, new EnemySearchState(), new EnemyGlobalState());

	mOwner->add(new EnemyVision(mOwner, this));
}


Enemy::~Enemy(){
	delete mStateMachine;
}


void Enemy::update(){
	mStateMachine->update();
	mCurrentFind = false;
}


void Enemy::draw(){

	Vec2D<int> gSize;
	GetGraphSize(mCurrentGID, &gSize.x, &gSize.y);
	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
				  mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
				  1.0, 0, mCurrentGID, true);


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


void Enemy::hit(GameObj* other){

	// マス、プレイヤーとの衝突を判定
	if( (dynamic_cast<Mass*>(other) != NULL && !(dynamic_cast<Mass*>(other)->isPass())) ||
		(dynamic_cast<Player*>(other) != NULL)
	   ){

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
		// その際にぶつかったオブジェクトのほうを向く
		if(abs(dy) >= abs(dx)){
			mPos.x += dx;
			changeDirection(((dx > 0) ? GameObj::DIRECTON_LEFT : GameObj::DIRECTON_RIGHT));
		}
		else{
			mPos.y += dy;
			changeDirection(((dy > 0) ? GameObj::DIRECTON_UP : GameObj::DIRECTON_DOWN));
		}

		// ぶつかったものがプレイヤーなら警戒ステートに移る
		if(dynamic_cast<Player*>(other) != NULL){
			mStateMachine->changeState(new EnemyCautionState());
		}

		// マスとぶつかったときは次のパトロール時もぶつからないようにパトロールの順序を変える
		if(dynamic_cast<Mass*>(other) != NULL){
			mNextPatrolPointElem *= -1;	
			mNextPatrolPointElem++;
			if(mNextPatrolPointElem >= (int)(mPatrolPoint.size())){
				mNextPatrolPointElem--;
			}
		}
	}

}


Vec2D<int> Enemy::nextPatrolPoint(){

	// 目的地に到達したら次の目的地へ行くように仕向ける
	if(mPatrolPoint[abs(mNextPatrolPointElem)] == mPos){
		
		//  方向転換
		if( (mNextPatrolPointElem + 1) >= (int)(mPatrolPoint.size()) ){
			mNextPatrolPointElem *= -1;
		}

		mNextPatrolPointElem++;
	}

	return mPatrolPoint[abs(mNextPatrolPointElem)];
}

// -------------------------------------------------------------------------------------------- //
// ------------------------------EnemyVisionクラスの実装--------------------------------------- //
// -------------------------------------------------------------------------------------------- //

EnemyVision::EnemyVision(GameObjContainer* ow, Enemy* enemy)
	:GameObj(ow, enemy->checkPos(), HitArea{Vec2D<int>(), Vec2D<int>()}){

	mEnemy = enemy;
}

void EnemyVision::update(){

	// Enemyの向きと座標に合わせてあたり判定と自分の座標を変化させる
	mPos = mEnemy->checkPos();
	int sign = 1;
	switch(mEnemy->checkDirection()){

		case DIRECTON_UP:
			sign = -1;
		case DIRECTON_DOWN:
			mHitArea.size.x = GameSceneParam::ENEMY_VISION_WIDTH;
			mHitArea.size.y = GameSceneParam::ENEMY_VISION_HEIGHT;
			mPos.y += sign * GameSceneParam::ENEMY_VISION_HEIGHT / 2;
			break;


		case DIRECTON_LEFT:
			sign = -1;
		case DIRECTON_RIGHT:
			mHitArea.size.y = GameSceneParam::ENEMY_VISION_WIDTH;
			mHitArea.size.x = GameSceneParam::ENEMY_VISION_HEIGHT;
			mPos.x += sign * GameSceneParam::ENEMY_VISION_HEIGHT / 2;
	}
}

void EnemyVision::draw(){
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y - (mHitArea.size.y / 2) + mHitArea.center.y,
			mPos.x + (mHitArea.size.x / 2) + mHitArea.center.x,
			mPos.y + (mHitArea.size.y / 2) + mHitArea.center.y,
			GetColor(0, 255, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif
}

// プレイヤー or 怪しいものを発見したらEnemyへ通知する
void EnemyVision::hit(GameObj* other){

	if(dynamic_cast<Player*>(other) != NULL){
		mEnemy->findMystericObj();
	}

}