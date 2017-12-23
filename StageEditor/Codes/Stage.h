//
// �ҏW���̃X�e�[�W�̏�������
//

#pragma once


#include <vector>
#include <string>
#include "MassData.h"
#include "Vec2DUtils.h"
#include "Button.h"
#include "GraphManager.h"
#include "EnemyData.h"


const int GRAPH_LAYER_NUM = 3;


class Stage{

private:
	enum layer_id{
		MASS_0 = 0,
		MASS_1,
		MASS_2,
		MASS_ELEM,
		ITEM,
		CHARA
	};

public:
	Stage();								// �����Ȃ��X�e�[�W���J��
	Stage(std::string);						// �����Ɏw�肳�ꂽjson�t�@�C���̃X�e�[�W���J��
	~Stage();
	void save(std::string);					// �����Ɏw�肳�ꂽpath�Ɍ���̃X�e�[�W��ۑ�����
	void draw();
	bool clickDetectAndAction();			// true���Ԃ����Ƃ���MainControll�̕��ɂ��̃}�X�ɒu������~���Ă���				
	void putDataToClickedTile(int);			// ���O�ŕۑ������}�X�Ɍ��݂̃��C���[�A�����ɏ]����������s��

	map_id checkCurrentTab();

private:
	std::vector<std::vector<MassData>> mMass[GRAPH_LAYER_NUM];
	std::string mName;
	Vec2D<int> mPushLog;						// �����ꂽ���ꂽ�Ƃ��̏�������
	Button mLayerChangeBtn;						// ���C���[�̕ύX(�}�X�A�A�C�e���A�L����)
	layer_id mCurrentLayer	= layer_id::MASS_0;
	Vec2D<int> mPlayerPos;
	std::vector<EnemyData> mEnemies;
	int mHoldEnemyElem = -1;					// ���݃p�g���[�������߂ő{�����̓G�f�[�^
	std::pair<int, int> mDate = {1, 1};			// �Q�[���ɔ��f������t�����i�[

};