//
// Stage�I�u�W�F�N�g���}�X�Ƃ��Ĉ����f�[�^�^�������Œ�`
//

#pragma once


#include <string>
#include "Param.h"


enum mass_elem{
	NORMAL,
	NOT_PASS,
	OBSTACLE
};


typedef struct{
	int gID			= -1;
	mass_elem elem	= NORMAL;
	int gItemID		= -1;
}MassData;
