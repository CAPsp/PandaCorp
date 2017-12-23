//
// �O���t�B�b�N���\�[�X���Ǘ�����N���X
// �� �܂��K�͂̏������Q�[���Ȃ̂ŃQ�[���N�����Ƀ��\�[�X����C�ɓǂݍ��ނ悤�Ȑ݌v�ɂȂ��Ă�
// �@ ��K�͂ɂȂ��Ă�����C������K�v������
//

#pragma once


#include <string>
#include <map>
#include <vector>
#include "Vec2DUtils.h"


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
	void clear();
	void load();								// ���\�[�X��ǂݍ���
	int checkID(std::string, Vec2D<int>);		// �����ɑΉ����郊�\�[�X�h�c��Ԃ�
	std::vector<int> getGraphIDs(std::string);	// �����ɑΉ�����p�X���̉摜�Q��Ԃ�

private:
	std::map<std::string, std::vector< std::pair<Vec2D<int>, int> >> mDatabase;

};