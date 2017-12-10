#include "Player.h"

#include "DxLib.h"
#include "GameSceneParam.h"
#include "InputManager.h"
#include "Mass.h"
#include "PlayerState.h"


Player::Player(int x, int y){

	mPos = Vec2D<int>(x, y);
	mHitAreaSize = Vec2D<int>(GameSceneParam::MASS_SIZE, GameSceneParam::MASS_SIZE);
	mVel = Vec2D<double>(0, 0);
	mStateMachine = new StateMachine<Player>(this, new PlayerStandState(), new PlayerGlobalState());
}


Player::~Player(){}


void Player::update(){
	mStateMachine->update();
}


void Player::draw(int){

#ifdef _DEBUG

	DrawFormatString(600, 0, GetColor(255, 0, 0), "V = (%.4lf, %.4lf)", mVel.x, mVel.y);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(mPos.x - (mHitAreaSize.x / 2),
			mPos.y - (mHitAreaSize.y / 2),
			mPos.x + (mHitAreaSize.x / 2),
			mPos.y + (mHitAreaSize.y / 2), GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
#endif

}


void Player::hit(GameObj* other){

	// �}�X�Ƃ̏Փ˂𔻒�
	Mass* tmp = dynamic_cast<Mass*>(other);
	if(tmp != NULL){

		if(!tmp->isPass()){

			// �ǂ̂��炢�d�Ȃ��Ă���̂����v�Z
			int dx;
			if(mPos.x <= other->checkPos().x){
				dx = (mPos.x + mHitAreaSize.x / 2) - (other->checkPos().x - other->checkHitArea().x / 2);
				dx *= (-1);
			}
			else{
				dx = (other->checkPos().x + other->checkHitArea().x / 2) - (mPos.x - mHitAreaSize.x / 2);
			}

			int dy;
			if(mPos.y <= other->checkPos().y){
				dy = (mPos.y + mHitAreaSize.y / 2) - (other->checkPos().y - other->checkHitArea().y / 2);
				dy *= (-1);
			}
			else{
				dy = (other->checkPos().y + other->checkHitArea().y / 2) - (mPos.y - mHitAreaSize.y / 2);
			}

			// �ړ����������Ȃ����ɓ����ďd�Ȃ���O��
			// �}�X�̂Ȃ��ڂœ����Ȃ��Ȃ�o�O���Ȃ������߂ɔ�r���Z�q�������_���ɕύX����
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