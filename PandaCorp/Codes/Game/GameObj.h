//
// あたり判定処理などのゲーム内オブジェクトの基本的な機能を持つクラス
// 基本的にステージ内に存在するものはこのクラスを継承している
//

#pragma once


#include "Vec2DUtils.h"


class GameObj{

public:
	GameObj() = default;
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1フレーム毎の更新処理
	virtual void draw(int)		= 0;	// 描画処理(引数は実装クラスによって扱いが変わる)
	virtual void hit(GameObj*)	= 0;	// 他のオブジェクトと衝突したときの処理

	bool checkCollide(const GameObj* other){

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

protected:
	Vec2D<int> mPos;
	Vec2D<int> mHitAreaSize;

};