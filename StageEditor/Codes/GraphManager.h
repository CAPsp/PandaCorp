//
// �O���t�B�b�N�̃��\�[�X���Ǘ�����
//

#pragma once


#include <string>
#include <map>
#include <vector>
#include "Vec2DUtils.h"
#include "Param.h"


enum map_id{
	MASS,
	CHARA,
	ITEM
};

struct graph_info{
	int gid = -1;
	std::string path = "";
	Vec2D<int> point;		// ������W
	bool is60h = false;		// ����60px�̂��̂�
};

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

	void load();	// ���\�[�X��ǂݍ���

	std::vector<int> getAllIDFromVec(map_id);			// map_id�Ŏw�肵��Map��ɂ��邷�ׂẴO���t�B�b�NID��Ԃ�
	//std::string searchPathFromMap(int, map_id);			// �@�@�@�@�@�V�@�@�@ �@�̗v�f��������ɓn����ID�ɑΉ�����O���t�B�b�N�̃p�X��Ԃ�
	//Vec2D<int> searchPosFromMap(int, map_id);
	//bool searchIs60pxFromMap(int, map_id);

	graph_info searchInfoFromMap(int, map_id);


	//graph_info checkID(std::string, map_id);			// �����ɑΉ����郊�\�[�X�h�c��Ԃ�

private:
	std::map<map_id, std::vector<graph_info>> mVec;

};