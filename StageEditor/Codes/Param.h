//
// �e��p�����[�^�������Œ�`
//

#pragma once


#include "Vec2DUtils.h"


#define GEN_DATA_DIR "GenData/"


struct graph_info{
	int gid = -1;
	std::string path = "";
	Vec2D<int> point;	// ������W
	bool is60h;			// ����60px�̂��̂�
};



namespace Param{

	const Vec2D<int> WINDOW_SIZE = {1280, 720};
	const Vec2D<int> STAGE_FRAME_SIZE = {920, WINDOW_SIZE.y};
	const Vec2D<int> RIGHT_FRAME_SIZE = {WINDOW_SIZE.x - STAGE_FRAME_SIZE.x, WINDOW_SIZE.y};

	const int COLOR_BIT_NUM = 16;

	const int MASS_SIZE = 40;
	const Vec2D<int> MASS_NUM = {23, 18};

	const int FONT_SIZE = 26;

}