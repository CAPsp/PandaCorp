//
// �t�@�C������֘A�̏��������郆�[�e�B���e�B�N���X
//

#pragma once


#include <vector>
#include <string>


class FileUtils{

public:

	// �����Ɏw�肵���f�B���N�g�����̃t�@�C���p�X��S�Ď擾����
	static std::vector<std::string> readPathInDir(std::string);

	// �����Ɏw�肵���f�B���N�g���ȉ��̃t�@�C���p�X��S�Ď擾����
	static std::vector<std::string> readPathBelowDir(std::string);

};