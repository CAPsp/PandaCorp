//
// �O���t�B�b�N���\�[�X���Ǘ�����N���X
// �� �܂��K�͂̏������Q�[���Ȃ̂ŃQ�[���N�����Ƀ��\�[�X����C�ɓǂݍ��ނ悤�Ȑ݌v�ɂȂ��Ă�
// �@ ��K�͂ɂȂ��Ă�����C������K�v������
//

#pragma once


#include <string>
#include <map>


// ������Ɠ���ȃV���O���g���p�^�[��
class GraphManager{

private:
	GraphManager() = default;
	~GraphManager();

public:
	GraphManager(const GraphManager&) = delete;
	GraphManager& operator=(const GraphManager&) = delete;
	GraphManager(GraphManager&&) = delete;
	GraphManager& operator=(GraphManager&&) = delete;

public:
	static GraphManager& getInstance(){
		static GraphManager obj;
		return obj;
	}
	void load();									// ���\�[�X��ǂݍ���
	int checkID(std::string);						// �����ɑΉ����郊�\�[�X�h�c��Ԃ�
	int getDerivGraph(std::string, int, int);	// �傫���摜�ɑ΂��Ĉ����ɉ������̈�𔲂��o��

private:
	std::map<std::string, int> mMap;

};