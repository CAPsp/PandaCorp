//
// �A�C�e�������i�[����N���X
//

#pragma once


#include "GameObj.h"


class Item : public GameObj{

public:
	Item(GameObjContainer*, Vec2D<int>, int, bool);
	virtual ~Item() = default;
	virtual void update(){}					// update�֐��ɂ��X�V�������Ȃ�
	virtual void hit(GameObj*){}
	virtual void draw();					// �ĕ`�掞�ɌĂяo��
	bool use();								// �A�C�e�����g�����ꍇ�̓���

	inline void toVisible(){ mIsVisible = true; }
	inline int checkGID(){ return mGraphID; }

private:
	int mGraphID;
	bool mIsVisible;

};