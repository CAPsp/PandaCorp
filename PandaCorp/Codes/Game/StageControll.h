//
// �Q�[���V�[����̃X�e�[�W���Ǘ�����N���X
//

#pragma once


#include <vector>
#include "GameObj.h"
#include "StageFile.h"
#include "GameObjContainer.h"


class StageControll{

public:
	StageControll(std::string);		// �ǂݍ���json�t�@�C�����w�肷��
	~StageControll();
	void update();					// 1�t���[�����̍X�V����

private:
	GameObjContainer mObjects;
	GameObjContainer mMasses;
	StageFile mStageFile;

};