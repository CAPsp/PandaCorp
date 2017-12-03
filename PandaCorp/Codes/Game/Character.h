//
// �L�����N�^�[�̏������N���X
//

#pragma once


#include "Vec2DUtils.h"
#include <vector>


class Character{

protected:
	enum chara_dir{
		U,
		R,
		D,
		L
	};

public:
	virtual void update(){}		// �X�V�����{�`��

protected:
	chara_dir mDir = chara_dir::U; 
	Vec2D<int> mPos;
	int mNowAnimElem = 0;			// TODO: Animation�N���X�ɕς��\��

};