//
// �X�e�[�W�̃}�X�����i�[����N���X
//

#pragma once


#include "GameObj.h"


class Mass : public GameObj{

public:
	Mass(GameObjContainer*, Vec2D<int>, int, bool);
	virtual ~Mass() = default;
	virtual void update(){}			// update�֐��ɂ��X�V�������Ȃ�
	virtual void hit(GameObj*);
	void draw();					// �ĕ`�掞�ɌĂяo��

public:
	inline bool isPass(){ return mPass; }

private:
	int mGraph;
	bool mPass;

};