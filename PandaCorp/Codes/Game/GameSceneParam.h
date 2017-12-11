#pragma once


#include "Vec2DUtils.h"


namespace GameSceneParam{

	const int MASS_SIZE = 40;
	const Vec2D<int> MASS_NUM = {24, 18};

	const int MASS_GRAPH_LAYER_NUM = 4;

	const double PLAYER_MAX_SPEED			= 4.0;
	const double PLAYER_ACCELE_PER_FRAME	= 1.0;
	const double PLAYER_VEL_RESISTANCE		= 0.2;	// ���݂̑��x�ɑ΂����R�l(1.0���ƈ�u�Ŏ~�܂�)
	
	// �A�j���͉��t���[���őJ�ڂ��邩
	const int ANIME_CHANGE_FRAME_NORMAL = 30;	
	const int ANIME_CHANGE_FRAME_QUICK	= 5;

};