//
// GameObjクラスを継承したものを扱うクラス
//

#pragma once


#include "GameObj.h"
#include <vector>


class GameObj;	// GameObjクラスと循環インクルード関係にあるため、その解決処理


class GameObjContainer{

public:
	GameObjContainer() = default;
	
	~GameObjContainer();

	inline int checkSize(){ return (int)(mVec.size()); }

	inline GameObj* checkElem(int num){ return mVec.at(num); }

	inline void add(GameObj* obj){ mTempAddVec.push_back(obj); }
	
	inline void remove(GameObj* obj){	mTempRemoveVec.push_back(obj);	}

	void update();	// GameObjの追加、削除、描画ソート処理を施すにはこれを呼ぶ必要がある
	
private:
	std::vector<GameObj*> mVec;
	std::vector<GameObj*> mTempAddVec;		// 新しく追加するGameObjを一時的に入れておく場所
	std::vector<GameObj*> mTempRemoveVec;	// 削除するGameObjを(ry

};