//
// �X�e�[�W�ɂ�����e�v�f��\������^�u
//

#pragma once


#include <vector>
#include "Vec2DUtils.h"
#include "GraphManager.h"


class MaterialTab{

public:
	MaterialTab(map_id);
	~MaterialTab(){}
	void clickDetectAndAction();		// �N���b�N���ꂽ�Ƃ��̏���
	void draw();
	inline const int getMassData(){ return mSelectDataGID; }

private:
	std::vector<int> mMassGraphID;
	int mSelectDataGID;		// �I�𒆂̃}�X�O���t�B�b�N�f�[�^
	Vec2D<int> mOrigin;		// ����`��ʒu�ƂȂ�ꏊ
	Vec2D<int> mMassNum;	// ���̃^�u��ɉ��̃}�X���u���邩

};