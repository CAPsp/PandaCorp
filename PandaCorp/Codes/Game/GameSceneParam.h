#pragma once


#include "Vec2DUtils.h"


namespace GameSceneParam{

	const int MASS_SIZE = 40;
	const Vec2D<int> MASS_NUM = {24, 18};

	const int MASS_GRAPH_LAYER_NUM = 4;

	const double PLAYER_MAX_SPEED			= 4.0;
	const double PLAYER_ACCELE_PER_FRAME	= 1.0;
	const double PLAYER_VEL_RESISTANCE		= 0.2;	// 現在の速度に対する抵抗値(1.0だと一瞬で止まる)
	
	// アニメは何フレームで遷移するか
	const int ANIME_CHANGE_FRAME_NORMAL = 30;	
	const int ANIME_CHANGE_FRAME_QUICK	= 5;

};