//
// �A�C�e���̏��������Œ�`
//

#pragma once


#include <string>
#include "Vec2DUtils.h"
#include "GlobalParam.h"


namespace ItemInfo{

	const std::string PATH = std::string(GRAPH_DIR_PATH) + "Item/item.png";

	//  �o�i�i
	const Vec2D<int> BANANA_POS		= Vec2D<int>(0, 0);

	// �p���V���[�g
	const Vec2D<int> PARACHUTE_POS	= Vec2D<int>(40, 0);

	// ��
	const Vec2D<int> KEY_POS		= Vec2D<int>(80, 0);
	
	// �g����
	const Vec2D<int> DOOL_POS		= Vec2D<int>(120, 0);

};
