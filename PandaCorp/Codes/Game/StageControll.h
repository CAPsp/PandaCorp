//
// �Q�[���V�[����̃X�e�[�W���Ǘ�����N���X
//

#pragma once


#include "StageFile.h"
#include "GameObjContainer.h"
#include "GameSceneParam.h"


class StageControll{

public:
	StageControll(std::string);		// �ǂݍ���json�t�@�C�����w�肷��
	~StageControll();
	void update();					// 1�t���[�����̍X�V����

private:
	GameObjContainer mObjects[2];	// �}�X + ���Q�[���I�u�W�F�N�g
	StageFile mStageFile;

};