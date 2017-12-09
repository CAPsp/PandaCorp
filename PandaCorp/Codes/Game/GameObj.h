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
	virtual void hit(GameObj&)	= 0;	// 他のオブジェクトと衝突したときの処理

protected:
	Vec2D<int> mPos;
	Vec2D<int> mHitAreaSize;

};