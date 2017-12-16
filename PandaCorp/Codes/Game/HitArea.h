//
// あたり判定処理に使われる構造体
//

#pragma once


#include "Vec2DUtils.h"


typedef struct{
	Vec2D<int> center;	// 相対的にみてあたり判定の中心となる部分
	Vec2D<int> size;	// あたり判定の大きさ
}HitArea;