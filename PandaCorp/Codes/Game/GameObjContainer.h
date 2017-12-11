//
// GameObjクラスを継承したものを扱うクラス
//

#pragma once


#include "GameObj.h"
#include <vector>
#include <algorithm>


class GameObj;	// GameObjクラスと循環インクルード関係にあるため、その解決処理


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

	// GameObjの追加、削除処理を施すにはこれを呼ぶ必要がある
	void update(){

		// 削除
		for(GameObj* obj : mTempRemoveVec){
			auto elem = std::find(mVec.begin(), mVec.end(), obj);
			if(elem != mVec.end()){
				mVec.erase(elem);
			}
		}
		mTempRemoveVec.clear();

		// 追加
		mVec.insert(mVec.end(), mTempAddVec.begin(), mTempAddVec.end());
		mTempAddVec.clear();
	}

private:
	std::vector<GameObj*> mVec;
	std::vector<GameObj*> mTempAddVec;		// 新しく追加するGameObjを一時的に入れておく場所
	std::vector<GameObj*> mTempRemoveVec;	// 削除するGameObjを(ry

};