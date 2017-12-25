#include "PlayerGenHitBox.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "Mass.h"
#include "PlayerState.h"
#include "Item.h"
#include "ItemStock.h"
#include "GameScene.h"
#include "SoundManager.h"


PlayerGenHitBox::PlayerGenHitBox(GameObjContainer* ow, Player* p)
	:mPlayer(p), GameObj(ow, Vec2D<int>(), HitArea{}){

	// �v���C���[�̑O���ɒu��
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

	// ���łɉ�������̃A�N�V���������Ă��画�肵�Ȃ�
	if(mDoAction){ return; }

	// �͂߂���̂���������͂�
	Mass* tmpMass = dynamic_cast<Mass*>(other);
	if(tmpMass != NULL){
		mDoAction = true;
		if(tmpMass->isObstacle()){
			mPlayer->getStateMachine()->changeState(new PlayerHoldState(tmpMass));
		}
		else if(tmpMass->isClear()){
			PlaySoundMem(SoundManager::getInstance().checkID("key.ogg"), DX_PLAYTYPE_BACK);
			GameScene::toClear();
		}
		else{
			mDoAction = false;
		}
	}
	
	// �A�C�e���擾
	if(dynamic_cast<Item*>(other) != NULL){
		other->checkOwner()->remove(other);
		mPlayer->getStateMachine()->changeState(new PlayerItemGetState());
		ItemStock::addItem(dynamic_cast<Item*>(other));
		GameScene::setUpCheckClearItemFlag();
		mDoAction = true;
	}

}