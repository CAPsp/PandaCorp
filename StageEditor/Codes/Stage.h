//
// �ҏW���̃X�e�[�W�̏�������
//

#pragma once


#include <vector>
#include <string>


class Stage{

public:
	Stage();											// �����Ȃ��X�e�[�W���J��
	Stage(std::string);									// �����Ɏw�肳�ꂽjson�t�@�C���̃X�e�[�W���J��
	void draw();
	void save(std::string);								// �����Ɏw�肳�ꂽpath�Ɍ���̃X�e�[�W��ۑ�����

private:
	std::vector<std::vector<int>> mMass;
	std::string mName;

};