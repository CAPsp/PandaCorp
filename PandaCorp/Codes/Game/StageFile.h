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
	std::string read(GameObjContainer*, int&);	// �n���ꂽvector�Ƀ}�X�I�u�W�F�N�g�Aint�ɍō��X�R�A��ǂݍ���

private:
	std::string mFilePath;

};