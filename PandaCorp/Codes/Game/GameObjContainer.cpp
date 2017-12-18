#include "GameObjContainer.h"

#include <algorithm>


GameObjContainer::~GameObjContainer(){
	for(GameObj* obj : mVec)			{ delete obj; }
	for(GameObj* obj : mTempAddVec)		{ delete obj; }
	for(GameObj* obj : mTempRemoveVec)	{ delete obj; }
}


void GameObjContainer::update(){

	// íœ
	for(GameObj* obj : mTempRemoveVec){
		auto elem = std::find(mVec.begin(), mVec.end(), obj);
		if(elem != mVec.end()){
			mVec.erase(elem);
		}
	}
	mTempRemoveVec.clear();

	// ’Ç‰Á
	mVec.insert(mVec.end(), mTempAddVec.begin(), mTempAddVec.end());
	mTempAddVec.clear();

	// •`‰æ‡‚Éƒ\[ƒg
	std::sort(	mVec.begin(),
				mVec.end(),
				[](GameObj* a, GameObj* b){return a->checkPos().y < b->checkPos().y; });
}