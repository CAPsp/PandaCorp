//
// �Q�[���V�[����̃X�e�[�W���Ǘ�����N���X
//

#pragma once


#include <vector>


class StageControll{

public:
	StageControll();
	~StageControll();
	void draw();		// �`�揈��

private:
	std::vector<std::vector<int>> mMass;	// TODO: Mass�^�����
	//std::vector<Character> mChara;
	//std::vector<Animation> mAnim;

};