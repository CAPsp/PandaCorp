//
// ����L�[�Ȃǂ��������Ƃ��Ƀv���C���[�O���ɂ�����̂����ʂ��邽�߂̃I�u�W�F�N�g
//

#pragma once


#include "GameObj.h"
#include "Player.h"


class PlayerGenHitBox : public GameObj{

public:
	PlayerGenHitBox() = delete;
	PlayerGenHitBox(GameObjContainer*, Player*);
	virtual ~PlayerGenHitBox() = default;
	virtual void update();	// 1�t���[����ɏ��ł���
	virtual void draw();
	virtual void hit(GameObj*);

private:
	Player* mPlayer;

};