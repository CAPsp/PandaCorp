//
// SE��BGM�̃��\�[�X���Ǘ�����N���X
// �� �܂��K�͂̏������Q�[���Ȃ̂ŃQ�[���N�����Ƀ��\�[�X����C�ɓǂݍ��ނ悤�Ȑ݌v�ɂȂ��Ă�
// �@ ��K�͂ɂȂ��Ă�����C������K�v������
//

#pragma once


#include <string>
#include <map>


// ������Ɠ���ȃV���O���g���p�^�[��
class SoundManager{

private:
	SoundManager() = default;
	~SoundManager();

public:
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = delete;
	SoundManager& operator=(SoundManager&&) = delete;

public:
	static SoundManager& getInstance(){
		static SoundManager obj;
		return obj;
	}
	void load();				// ���\�[�X��ǂݍ���
	int checkID(std::string);	// �����ɑΉ����郊�\�[�X�h�c��Ԃ�

private:
	std::map<std::string, int> mMap;

};