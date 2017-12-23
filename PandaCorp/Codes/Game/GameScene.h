#pragma once


#include "BaseScene.h"
#include "StageControll.h"
#include "StageEndProcess.h"
#include "ItemStock.h"


class GameScene : public BaseScene{

public:
	GameScene(int){}
	virtual ~GameScene() = default;
	virtual scene_sig update();
	virtual bool begin();
	virtual bool end();
	void uiDraw();	// UI��`�悷�鏈��

// �X�e�[�W�I�����������Ƃ��ɌĂ΂��ÓI�֐��Q
public:
	static void toGameOver(){ sEndProcess.gameover(); }
	static void toClear(){ sEndProcess.clear(); }
	static void toStageSelect(){ sEndProcess.returnStageSelect(); }

private:
	StageControll* mStage;
	static StageEndProcess sEndProcess;
	int mStageNameFontHandle;
	std::pair<int, int> mDate;	// �Q�[�����̓��t
	int mProgressFrame = 0;		// �Q�[���J�n����o�߂����t���[��
	ItemStock mItemStock;

};