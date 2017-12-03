//
// ステージのマス情報を格納するクラス
//

#pragma once


#include "GameSceneParam.h"


class Mass{

public:
	Mass() = default;
	~Mass() = default;

public:
	int mGID[GameSceneParam::MASS_GRAPH_LAYER_NUM] = {-1, -1, -1};
	bool mPass = true;

};