//
// キャラクターの情報を持つクラス
//

#pragma once


#include "Vec2DUtils.h"
#include <vector>


class Character{

protected:
	enum chara_dir{
		U,
		R,
		D,
		L
	};

public:
	virtual void update(){}		// 更新処理＋描画

protected:
	chara_dir mDir = chara_dir::U; 
	Vec2D<int> mPos;
	int mNowAnimElem = 0;			// TODO: Animationクラスに変わる予定

};