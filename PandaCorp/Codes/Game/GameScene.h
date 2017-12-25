#pragma once


#include "BaseScene.h"
#include "StageControll.h"
#include "StageEndProcess.h"
#include "ItemStock.h"


class GameScene : public BaseScene{

public:
	GameScene(int num):mStageNum(num){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();
	void uiDraw();				// UI��`�悷�鏈��

// �X�e�[�W�I�����������Ƃ��ɌĂ΂��ÓI�֐��Q
public:
	static void toGameOver();
	static void toClear();
	static void toStageSelect();

public:
	static void setUpCheckClearItemFlag(){ sNextCheckClearItemFlag = true; }

private:
	int mStageNum = 1;
	StageControll* mStage;
	int mStageNameFontHandle;
	std::pair<int, int> mDate;	// �Q�[�����̓��t
	int mProgressFrame = 0;		// �Q�[���J�n����o�߂����t���[��
	ItemStock mItemStock;
	int mSelectedItemElem;
	bool mMainSoundStartFlag = false;

private:
	static StageEndProcess sEndProcess;
	static bool sNextCheckClearItemFlag;	// ���̃t���O����������}�X�̃N���A������s��

};