//
// �����蔻�菈���Ȃǂ̃Q�[�����I�u�W�F�N�g�̊�{�I�ȋ@�\�����N���X
// ��{�I�ɃX�e�[�W���ɑ��݂�����̂͂��̃N���X���p�����Ă���
//

#pragma once


#include "Vec2DUtils.h"


class GameObj{

public:
	GameObj() = default;
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1�t���[�����̍X�V����
	virtual void hit(GameObj&)	= 0;	// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̏���

protected:
	Vec2D<int> mPos;
	Vec2D<int> mHitAreaSize;

};