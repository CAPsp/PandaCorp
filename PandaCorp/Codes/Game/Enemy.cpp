#include "Enemy.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "EnemyState.h"
#include "Mass.h"


Enemy::Enemy(GameObjContainer* ow, Vec2D<int> pos)
	:GameObj(ow, pos, HitArea{Vec2D<int>(0, 0), Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE)}){

	mStateMachine = new StateMachine<Enemy>(this, new EnemySearchState(), new EnemyGlobalState());
}


Enemy::~Enemy(){
	delete mStateMachine;
}


void Enemy::update(){
	mStateMachine->update();
}


void Enemy::draw(){

	Vec2D<int> gSize;
	GetGraphSize(mCurrentGID, &gSize.x, &gSize.y);
	DrawRotaGraph(mPos.x - (gSize.x - GameSceneParam::MASS_SIZE) / 2,
				  mPos.y - (gSize.y - GameSceneParam::MASS_SIZE) / 2,
				  1.0, 0, mCurrentGID, true);
}


void Enemy::hit(GameObj* other){

	// �}�X�A���̓G�Ƃ̏Փ˂𔻒�
	if( (dynamic_cast<Mass*>(other) != NULL && !(dynamic_cast<Mass*>(other)->isPass())) ||
		(dynamic_cast<Enemy*>(other) != NULL)
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
		// �}�X�̂Ȃ��ڂœ����Ȃ��Ȃ�o�O���Ȃ������߂ɔ�r���Z�q�������_���ɕύX����
		static bool flag;
		flag = GetRand(1);
		if((flag && abs(dy) >= abs(dx)) || (!flag && abs(dy) > abs(dx))){
			mPos.x += dx;
		}
		else{
			mPos.y += dy;
		}
	}

}