//
// 特別なマスグラフィックは何かを定義する
//

#pragma once


#include <string>
#include <vector>
#include "Vec2DUtils.h"
#include "GlobalParam.h"


namespace SpecialMass{

	// ドア
	const std::string DOOR_GRAPH_PATH = (std::string(GRAPH_DIR_PATH) + "Mass/h60/chip.png");
	const std::vector<Vec2D<int>> DOOR_GRAPH_POS = {
		Vec2D<int>(0, 60),
		Vec2D<int>(40, 60)
	};

	// 窓
	const std::string WINDOW_GRAPH_PATH = (std::string(GRAPH_DIR_PATH) + "Mass/h60/chip.png");
	const std::vector<Vec2D<int>> WINDOW_GRAPH_POS = {
		Vec2D<int>(80, 60),
		Vec2D<int>(0, 120),
		Vec2D<int>(40, 120),
		Vec2D<int>(80, 120),
		Vec2D<int>(120, 120),
		Vec2D<int>(160, 120),
		Vec2D<int>(200, 120)
	};

};
