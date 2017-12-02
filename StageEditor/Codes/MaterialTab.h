//
// �X�e�[�W�ɂ�����}�X��\������^�u
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"
#include "MassData.h"


class MaterialTab{

public:
	MaterialTab();
	~MaterialTab(){}
	void clickDetectAndAction();		// �N���b�N���ꂽ�Ƃ��̏���
	void draw();
	inline const MassData getMassData(){ return mSelectData; }

private:
	std::vector<int> mMassGraphID;
	MassData mSelectData;
	Vec2D<int> mOrigin;		// ����`��ʒu�ƂȂ�ꏊ
	Vec2D<int> mMassNum;	// ���̃^�u��ɉ��̃}�X���u���邩

};