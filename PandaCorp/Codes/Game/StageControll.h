//
// �Q�[���V�[����̃X�e�[�W���Ǘ�����N���X
//

#pragma once


#include <vector>
#include "Mass.h"
#include "GameObj.h"
#include "StageFile.h"


class StageControll{

public:
	StageControll(std::string);		// �ǂݍ���json�t�@�C�����w�肷��
	~StageControll();
	void update();					// 1�t���[�����̍X�V����

private:
	std::vector<GameObj*> mObjects;
	std::vector<Mass*> mMasses;
	StageFile mStageFile;

};