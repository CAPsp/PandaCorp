//
// Stage�I�u�W�F�N�g���}�X�Ƃ��Ĉ����f�[�^�^�������Œ�`
//

#pragma once


#include <string>

const int JSON_LAYER_NUM = 3;

typedef struct{
	int gID[JSON_LAYER_NUM]				= {-1, -1, -1};
	std::string gPath[JSON_LAYER_NUM]	= {"", "", ""};
	bool pass							= true;
	std::string charaPath				= "";
	std::string itemPath				= "";
}MassData;
