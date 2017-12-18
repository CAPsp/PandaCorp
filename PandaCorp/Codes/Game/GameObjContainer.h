//
// GameObj�N���X���p���������̂������N���X
//

#pragma once


#include "GameObj.h"
#include <vector>


class GameObj;	// GameObj�N���X�Əz�C���N���[�h�֌W�ɂ��邽�߁A���̉�������


class GameObjContainer{

public:
	GameObjContainer() = default;
	
	~GameObjContainer();

	inline int checkSize(){ return (int)(mVec.size()); }

	inline GameObj* checkElem(int num){ return mVec.at(num); }

	inline void add(GameObj* obj){ mTempAddVec.push_back(obj); }
	
	inline void remove(GameObj* obj){	mTempRemoveVec.push_back(obj);	}

	void update();	// GameObj�̒ǉ��A�폜�A�`��\�[�g�������{���ɂ͂�����ĂԕK�v������
	
private:
	std::vector<GameObj*> mVec;
	std::vector<GameObj*> mTempAddVec;		// �V�����ǉ�����GameObj���ꎞ�I�ɓ���Ă����ꏊ
	std::vector<GameObj*> mTempRemoveVec;	// �폜����GameObj��(ry

};