//
// �X�e�[�W�t�@�C������舵���N���X
//

#pragma once


#include <string>
#include <vector>
#include "GameObj.h"
#include "GameObjContainer.h"


class StageFile{

public:
	StageFile(std::string);
	~StageFile() = default;
	std::string read(GameObjContainer*);	// �n���ꂽvector�Ƀ}�X�I�u�W�F�N�g��ǂݍ���

private:
	std::string mFilePath;

};