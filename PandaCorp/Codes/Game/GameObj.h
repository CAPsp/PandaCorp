//
// �����蔻�菈���Ȃǂ̃Q�[�����I�u�W�F�N�g�̊�{�I�ȋ@�\�����N���X
// ��{�I�ɃX�e�[�W���ɑ��݂�����̂͂��̃N���X���p�����Ă���
//

#pragma once


#include "Vec2DUtils.h"
#include <vector>
#include "GameObjContainer.h"
#include "HitArea.h"


class GameObjContainer;	// GameObjContainer// GameObj�N���X�Əz�C���N���[�h�֌W�ɂ��邽�߁A���̉��������N���X�Əz�C���N���[�h�֌W�ɂ��邽�߁A���̉�������


class GameObj{

// �����Ă���������Ӗ�����萔
public:
	static const char DIRECTON_UP		= 'u';
	static const char DIRECTON_DOWN		= 'd';
	static const char DIRECTON_LEFT		= 'l';
	static const char DIRECTON_RIGHT	= 'r';
	
public:
	GameObj() = delete;
	GameObj(GameObjContainer* ow, Vec2D<int> pos, HitArea hit)
		:mOwner(ow), mPos(pos), mHitArea(hit){}
	virtual ~GameObj() = default;
	virtual void update()		= 0;	// 1�t���[�����̍X�V����
	virtual void draw()			= 0;	// �`�揈��(�����͎����N���X�ɂ���Ĉ������ς��)
	virtual void hit(GameObj*)	= 0;	// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̏���

	bool checkCollide(const GameObj* other){

		// �����蔻��G���A��0�̂��̂̏ꍇ�A�v�Z�̍l�������Ȃ�
		if( (mHitArea.size.x == 0 && mHitArea.size.y == 0) ||
			(other->mHitArea.size.x == 0 && other->mHitArea.size.y == 0) ){
		
			return false;
		}

		// ��_������ɂ���
		Vec2D<int> p(mPos.x - mHitArea.size.x / 2 + mHitArea.center.x,
					 mPos.y - mHitArea.size.y / 2 + mHitArea.center.y);
		Vec2D<int> op(other->mPos.x - other->mHitArea.size.x / 2 + other->mHitArea.center.x,
					  other->mPos.y - other->mHitArea.size.y / 2 + other->mHitArea.center.y);
		
		return ((p.x	< (op.x	+ other->mHitArea.size.x)) &&
				(op.x	< (p.x	+ mHitArea.size.x)) &&
				(p.y	< (op.y	+ other->mHitArea.size.y)) &&
				(op.y	< (p.y	+ mHitArea.size.y)) );
	}

public:
	inline Vec2D<int> checkPos()		{ return mPos; }
	inline HitArea checkHitArea()		{ return mHitArea; }
	inline void movePos(Vec2D<int> p)	{ mPos += p; }	// ���ݒn�_����_�Ƃ��Ĉړ�������
	inline void changeHitAreaSize(Vec2D<int> size)		{ mHitArea.size = size; }
	inline void changeHitAreaCenter(Vec2D<int> center)	{ mHitArea.center = center; }

protected:
	Vec2D<int> mPos;
	HitArea mHitArea;
	GameObjContainer* mOwner;			// ���g���Ǘ����Ă���vector�ւ̃|�C���^

};