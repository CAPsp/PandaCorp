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

	// �}�X�A�v���C���[�Ƃ̏Փ˂𔻒�
	if( (dynamic_cast<Mass*>(other) != NULL && !(dynamic_cast<Mass*>(other)->isPass())) ||
		(dynamic_cast<Player*>(other) != NULL)
	   ){

		// �ǂ̂��炢�d�Ȃ��Ă���̂����v�Z
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

		// �ړ����������Ȃ����ɓ����ďd�Ȃ���O��
		// ���̍ۂɂԂ������I�u�W�F�N�g�̂ق�������
		if(abs(dy) >= abs(dx)){
			mPos.x += dx;
			changeDirection(((dx > 0) ? GameObj::DIRECTON_LEFT : GameObj::DIRECTON_RIGHT));
		}
		else{
			mPos.y += dy;
			changeDirection(((dy > 0) ? GameObj::DIRECTON_UP : GameObj::DIRECTON_DOWN));
		}

		// �Ԃ��������̂��v���C���[�Ȃ�x���X�e�[�g�Ɉڂ�
		if(dynamic_cast<Player*>(other) != NULL){
			mStateMachine->changeState(new EnemyCautionState());
		}

		// �}�X�ƂԂ������Ƃ��͎��̃p�g���[�������Ԃ���Ȃ��悤�Ƀp�g���[���̏�����ς���
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

	// �ړI�n�ɓ��B�����玟�̖ړI�n�֍s���悤�Ɏd������
	if(mPatrolPoint[abs(mNextPatrolPointElem)] == mPos){
		
		//  �����]��
		if( (mNextPatrolPointElem + 1) >= (int)(mPatrolPoint.size()) ){
			mNextPatrolPointElem *= -1;
		}

		mNextPatrolPointElem++;
	}

	return mPatrolPoint[abs(mNextPatrolPointElem)];
}

// -------------------------------------------------------------------------------------------- //
// ------------------------------EnemyVision�N���X�̎���--------------------------------------- //
// -------------------------------------------------------------------------------------------- //

EnemyVision::EnemyVision(GameObjContainer* ow, Enemy* enemy)
	:GameObj(ow, enemy->checkPos(), HitArea{Vec2D<int>(), Vec2D<int>()}){

	mEnemy = enemy;
}

void EnemyVision::update(){

	// Enemy�̌����ƍ��W�ɍ��킹�Ă����蔻��Ǝ����̍��W��ω�������
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

// �v���C���[ or ���������̂𔭌�������Enemy�֒ʒm����
void EnemyVision::hit(GameObj* other){

	if(dynamic_cast<Player*>(other) != NULL){
		mEnemy->findMystericObj();
	}

}