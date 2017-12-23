//
// �X�e�[�W�̃}�X�����i�[����N���X
//

#pragma once


#include "GameObj.h"
#include "Player.h"


class Mass : public GameObj{

public:
	enum mass_elem{
		NORMAL,
		NOT_PASS,
		OBSTACLE
	};

public:
	Mass(GameObjContainer*, Vec2D<int>, int, mass_elem = NORMAL);
	virtual ~Mass() = default;
	virtual void update(){}			// update�֐��ɂ��X�V�������Ȃ�
	virtual void hit(GameObj*);
	void draw();					// �ĕ`�掞�ɌĂяo��

public:
	inline mass_elem checkElem(){ return mElem; }
	inline bool isPass(){ return mElem == NORMAL; }
	inline bool isObstacle(){ return mElem == OBSTACLE; }
	//inline void setElem(mass_elem elem){ mElem = elem; }

private:
	int mGraph;
	mass_elem mElem;

};