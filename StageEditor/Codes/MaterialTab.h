//
// �X�e�[�W�ɂ�����}�X��\������^�u
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"


class MaterialTab{

public:
	MaterialTab();
	~MaterialTab(){}
	void process();		// �N���b�N���ꂽ�Ƃ��̏���
	void draw();

private:
	std::vector<int> mMassGraphID;
	int mSelectGraph = -1;
	Vec2D<int> mOrigin;		// ����`��ʒu�ƂȂ�ꏊ
	Vec2D<int> mMassNum;	// ���̃^�u��ɉ��̃}�X���u���邩

};