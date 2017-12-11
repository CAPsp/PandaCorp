//
// あたり判定処理などのゲーム内オブジェクトの基本的な機能を持つクラス
// 基本的にステージ内に存在するものはこのクラスを継承している
//

#pragma once


#include "Vec2DUtils.h"
#include <vector>
#include "GameObjContainer.h"


class GameObjContainer;// GameObjContainer// GameObjクラスと循環インクルード関係にあるため、その解決処理クラスと循環インクルード関係にあるため、その解決処理


class GameObj{

// 向いている方向を意味する定数
public:
	static const char DIRECTON_UP		= 'u';
	static const char DIRECTON_DOWN		= 'd';
	static const char DIRECTON_LEFT		= 'l';
	static const char DIRECTON_RIGHT	= 'r';
	
public:
	GameObj() = delete;
	GameObj(GameObjContainer* ow, Vec2D<int> pos, Vec2D<int> hit)
		:mOwner(ow), mPos(pos), mHitAreaSize(hit){}
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1フレーム毎の更新処理
	virtual void draw()		= 0;	// 描画処理(引数は実装クラスによって扱いが変わる)
	virtual void hit(GameObj*)	= 0;	// 他のオブジェクトと衝突したときの処理

	bool checkCollide(const GameObj* other){

		// あたり判定エリアが0のものの場合、計算の考慮をしない
		if( (mHitAreaSize.x == 0 && mHitAreaSize.y == 0) || 
			(other->mHitAreaSize.x == 0 && other->mHitAreaSize.y == 0) ){
		
			return false;
		}

		// 基準点を左上にする
		Vec2D<int> p(mPos.x - mHitAreaSize.x / 2,					mPos.y - mHitAreaSize.y / 2);
		Vec2D<int> op(other->mPos.x - other->mHitAreaSize.x / 2,	other->mPos.y - other->mHitAreaSize.y / 2);
		
		return ((p.x	< (op.x	+ other->mHitAreaSize.x		)) &&
				(op.x	< (p.x		+ mHitAreaSize.x		)) &&
				(p.y	< (op.y	+ other->mHitAreaSize.y		)) &&
				(op.y	< (p.y		+ mHitAreaSize.y		)) );
	}

public:
	inline Vec2D<int> checkPos()	{ return mPos; }
	inline Vec2D<int> checkHitArea(){ return mHitAreaSize; }
	inline void movePos(Vec2D<int> p){ mPos += p; }	// 現在地点を基点として移動をする

protected:
	Vec2D<int> mPos;
	Vec2D<int> mHitAreaSize;
	GameObjContainer* mOwner;	// 自身を管理しているvectorへのポインタ

};