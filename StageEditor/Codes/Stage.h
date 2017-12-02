//
// �ҏW���̃X�e�[�W�̏�������
//

#pragma once


#include <vector>
#include <string>
#include "MassData.h"
#include "Vec2DUtils.h"
#include "Button.h"


class Stage{

private:
	static const int LAYER_NUM = 3;

public:
	Stage();								// �����Ȃ��X�e�[�W���J��
	Stage(std::string);						// �����Ɏw�肳�ꂽjson�t�@�C���̃X�e�[�W���J��
	~Stage();
	void save(std::string);					// �����Ɏw�肳�ꂽpath�Ɍ���̃X�e�[�W��ۑ�����
	void draw();
	bool clickDetectAndAction();			// true���Ԃ����Ƃ���MainControll�̕��ɂ��̃}�X�ɒu������~���Ă���				
	void putDataToClickedTile(MassData);	// ���O�ŕۑ������}�X�Ɉ����̃f�[�^��u��

private:
	std::vector<std::vector<MassData>> mMass[LAYER_NUM];
	std::string mName;
	Vec2D<int> mClickLog;		// �N���b�N���ꂽ�Ƃ��̏�������
	Button *mLayerChangeBtn = nullptr;
	int mCurrentLayer = 0;

};