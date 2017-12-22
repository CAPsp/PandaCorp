#pragma once

#include <vector>
#include "Vec2DUtils.h"


typedef struct{
	int gID = -1;
	std::vector<Vec2D<int>> patrolVec;
}EnemyData;