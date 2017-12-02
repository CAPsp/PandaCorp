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
	enum layer_id{
		MASS_0,
		MASS_1,
		MASS_2,
		PASS,
		CHARA,
		ITEM
	};

public:
	Stage();								// �����Ȃ��X�e�[�W���J��
	Stage(std::string);						// �����Ɏw�肳�ꂽjson�t�@�C���̃X�e�[�W���J��
	~Stage();
	void save(std::string);					// �����Ɏw�肳�ꂽpath�Ɍ���̃X�e�[�W��ۑ�����
	void draw();
	bool clickDetectAndAction();			// true���Ԃ����Ƃ���MainControll�̕��ɂ��̃}�X�ɒu������~���Ă���				
	void putDataToClickedTile(MassData);	// ���O�ŕۑ������}�X�Ɉ����̃f�[�^��u��

private:
	std::vector<std::vector<MassData>> mMass;
	std::string mName;
	Vec2D<int> mPushLog;		// �����ꂽ���ꂽ�Ƃ��̏�������
	Button *mLayerChangeBtn = nullptr;
	layer_id mCurrentLayer = layer_id::MASS_0;

};