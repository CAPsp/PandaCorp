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


enum item_elem{
	NOTING,
	VISIBLE,
	UNVISIBLE
};


typedef struct{
	int gID				= -1;
	mass_elem elem		= NORMAL;
	item_elem itemElem	= NOTING;
}MassData;
