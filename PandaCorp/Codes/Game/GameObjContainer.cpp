#include "GameObjContainer.h"

#include <algorithm>


GameObjContainer::~GameObjContainer(){
	for(GameObj* obj : mVec)			{ delete obj; }
	for(GameObj* obj : mTempAddVec)		{ delete obj; }
	for(GameObj* obj : mTempRemoveVec)	{ delete obj; }
}


void GameObjContainer::update(){

	// �폜
	for(GameObj* obj : mTempRemoveVec){
		auto elem = std::find(mVec.begin(), mVec.end(), obj);
		if(elem != mVec.end()){
			mVec.erase(elem);
		}
	}
	mTempRemoveVec.clear();

	// �ǉ�
	mVec.insert(mVec.end(), mTempAddVec.begin(), mTempAddVec.end());
	mTempAddVec.clear();

	// �`�揇�Ƀ\�[�g
	std::sort(	mVec.begin(),
				mVec.end(),
				[](GameObj* a, GameObj* b){return a->checkPos().y < b->checkPos().y; });
}