//
// �����蔻�菈���Ȃǂ̃Q�[�����I�u�W�F�N�g�̊�{�I�ȋ@�\�����N���X
// ��{�I�ɃX�e�[�W���ɑ��݂�����̂͂��̃N���X���p�����Ă���
//

#pragma once


#include "Vec2DUtils.h"


class GameObj{

// �����Ă���������Ӗ�����萔
public:
	static const char DIRECTON_UP		= 'u';
	static const char DIRECTON_DOWN		= 'd';
	static const char DIRECTON_LEFT		= 'l';
	static const char DIRECTON_RIGHT	= 'r';
	
public:
	GameObj() = default;
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1�t���[�����̍X�V����
	virtual void draw(int)		= 0;	// �`�揈��(�����͎����N���X�ɂ���Ĉ������ς��)
	virtual void hit(GameObj*)	= 0;	// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̏���

	bool checkCollide(const GameObj* other){

		// ��_������ɂ���
		Vec2D<int> p(mPos.x - mHitAreaSize.x / 2,					mPos.y - mHitAreaSize.y / 2);
		Vec2D<int> op(other->mPos.x - other->mHitAreaSize.x / 2,	other->mPos.y - other->mHitAreaSize.y / 2);
		
		return ((p.x	< (op.x	+ other->mHitAreaSize.x		)) &&
				(op.x	< (p.x		+ mHitAreaSize.x		)) &&
				(p.y	< (op.y	+ other->mHitAreaSize.y		)) &&
				(op.y	< (p.y		+ mHitAreaSize.y		)) );
	}

public:
	inline Vec2D<int> checkPos()	{ return mPos; }
	inline Vec2D<int> checkHitArea(){ return mHitAreaSize; }
	inline void movePos(Vec2D<int> p){ mPos += p; }	// ���ݒn�_����_�Ƃ��Ĉړ�������

protected:
	Vec2D<int> mPos;
	Vec2D<int> mHitAreaSize;

};