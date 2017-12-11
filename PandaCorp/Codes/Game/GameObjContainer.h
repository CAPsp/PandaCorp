//
// GameObj�N���X���p���������̂������N���X
//

#pragma once


#include "GameObj.h"
#include <vector>
#include <algorithm>


class GameObj;	// GameObj�N���X�Əz�C���N���[�h�֌W�ɂ��邽�߁A���̉�������


class GameObjContainer{

public:
	GameObjContainer() = default;
	
	~GameObjContainer(){
		for(GameObj* obj : mVec)			{ delete obj; }
		for(GameObj* obj : mTempAddVec)		{ delete obj; }
		for(GameObj* obj : mTempRemoveVec)	{ delete obj; }
	}

	inline int checkSize(){ return (int)(mVec.size()); }

	inline GameObj* checkElem(int num){ return mVec.at(num); }

	inline void add(GameObj* obj){ mTempAddVec.push_back(obj); }
	
	inline void remove(GameObj* obj){	mTempRemoveVec.push_back(obj);	}

	// GameObj�̒ǉ��A�폜�������{���ɂ͂�����ĂԕK�v������
	void update(){

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
	}

private:
	std::vector<GameObj*> mVec;
	std::vector<GameObj*> mTempAddVec;		// �V�����ǉ�����GameObj���ꎞ�I�ɓ���Ă����ꏊ
	std::vector<GameObj*> mTempRemoveVec;	// �폜����GameObj��(ry

};