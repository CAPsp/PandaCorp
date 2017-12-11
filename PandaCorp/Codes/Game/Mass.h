//
// �X�e�[�W�̃}�X�����i�[����N���X
//

#pragma once


#include "GameObj.h"


class Mass : public GameObj{

public:
	static const int LAYER_NUM = 4;		// �}�X�摜�R���ƃA�C�e��

public:
	Mass(GameObjContainer*, Vec2D<int>, std::vector<int>, bool);
	virtual ~Mass() = default;
	virtual void update(){}			// update�֐��ɂ��X�V�������Ȃ�
	virtual void hit(GameObj*);
	void draw(int);					// �ĕ`�掞�ɌĂяo��

public:
	inline bool isPass(){ return mPass; }

private:
	std::vector<int> mGraphs;
	bool mPass;

};