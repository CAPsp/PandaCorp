#pragma once


#include "Vec2DUtils.h"
#include "GlobalParam.h"


namespace GameSceneParam{

	const Vec2D<int> STAGE_FRAME_SIZE = {920, GlobalParam::WINDOW_SIZE.y};

	const int MASS_SIZE = 40;
	const Vec2D<int> MASS_NUM = {23, 18};

	const double PLAYER_MAX_SPEED			= 4.0;
	const double PLAYER_ACCELE_PER_FRAME	= 1.0;
	const double PLAYER_VEL_RESISTANCE		= 0.2;	// ���݂̑��x�ɑ΂����R�l(1.0���ƈ�u�Ŏ~�܂�)
	
	// �A�j���͉��t���[���őJ�ڂ��邩
	const int ANIME_CHANGE_FRAME_NORMAL = 30;	
	const int ANIME_CHANGE_FRAME_QUICK	= 5;

	// �G�̎��E�����̒�`
	const int ENEMY_VISION_HEIGHT	= 200;
	const int ENEMY_VISION_WIDTH	= 80;

	// �I�Ǝ��ԁi�Q�[���͂�������J�n����j
	const int CLOSING_TIME_HOUR		= 18;
	const int CLOSING_TIME_MINUTE	= 30;

};