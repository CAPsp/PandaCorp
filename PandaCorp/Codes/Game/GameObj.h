//
// あたり判定処理などのゲーム内オブジェクトの基本的な機能を持つクラス
// 基本的にステージ内に存在するものはこのクラスを継承している
//

#pragma once


#include "Vec2DUtils.h"
#include <vector>
#include "GameObjContainer.h"
#include "HitArea.h"


class GameObjContainer;	// GameObjContainer// GameObjクラスと循環インクルード関係にあるため、その解決処理クラスと循環インクルード関係にあるため、その解決処理


class GameObj{

// 向いている方向を意味する定数
public:
	static const char DIRECTON_UP		= 'u';
	static const char DIRECTON_DOWN		= 'd';
	static const char DIRECTON_LEFT		= 'l';
	static const char DIRECTON_RIGHT	= 'r';
	
public:
	GameObj() = delete;
	GameObj(GameObjContainer* ow, Vec2D<int> pos, HitArea hit)
		:mOwner(ow), mPos(pos), mHitArea(hit){}
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1フレーム毎の更新処理
	virtual void draw()			= 0;	// 描画処理(引数は実装クラスによって扱いが変わる)
	virtual void hit(GameObj*)	= 0;	// 他のオブジェクトと衝突したときの処理

	bool checkCollide(const GameObj* other){

		// あたり判定エリアが0のものの場合、計算の考慮をしない
		if( (mHitArea.size.x == 0 && mHitArea.size.y == 0) ||
			(other->mHitArea.size.x == 0 && other->mHitArea.size.y == 0) ){
		
			return false;
		}

		// 基準点を左上にする
		Vec2D<int> p(mPos.x - mHitArea.size.x / 2 + mHitArea.center.x,
					 mPos.y - mHitArea.size.y / 2 + mHitArea.center.y);
		Vec2D<int> op(other->mPos.x - other->mHitArea.size.x / 2 + other->mHitArea.center.x,
					  other->mPos.y - other->mHitArea.size.y / 2 + other->mHitArea.center.y);
		
		return ((p.x	< (op.x	+ other->mHitArea.size.x)) &&
				(op.x	< (p.x	+ mHitArea.size.x)) &&
				(p.y	< (op.y	+ other->mHitArea.size.y)) &&
				(op.y	< (p.y	+ mHitArea.size.y)) );
	}

public:
	inline Vec2D<int> checkPos()		{ return mPos; }
	inline HitArea checkHitArea()		{ return mHitArea; }
	inline void movePos(Vec2D<int> p)	{ mPos += p; }	// 現在地点を基点として移動をする
	inline void changeHitAreaSize(Vec2D<int> size)		{ mHitArea.size = size; }
	inline void changeHitAreaCenter(Vec2D<int> center)	{ mHitArea.center = center; }

protected:
	Vec2D<int> mPos;
	HitArea mHitArea;
	GameObjContainer* mOwner;			// 自身を管理しているvectorへのポインタ

};