//
// �Q�[���V�[����̃X�e�[�W���Ǘ�����N���X
//

#pragma once


#include <vector>
#include "Mass.h"
#include "Character.h"


class StageControll{

public:
	StageControll(std::string);		// �ǂݍ���json�t�@�C�����w�肷��
	~StageControll();
	void update();					// 1�t���[�����̍X�V����

private:
	std::vector<std::vector<Mass>> mMass;
	std::vector<Character*> mChara;
	//std::vector<Animation> mAnim;

};