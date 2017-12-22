//
// グラフィックのリソースを管理する
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
	Vec2D<int> point;		// 左上座標
	bool is60h = false;		// 高さ60pxのものか
};

// ちょっと特殊なシングルトンパターン
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

	void load();	// リソースを読み込む

	std::vector<int> getAllIDFromVec(map_id);		// map_idで指定したMap上にあるすべてのグラフィックIDを返す
	graph_info searchInfoFromMap(int, map_id);		//               〃           指定されたＩＤのグラ情報を返す
	int checkGID(std::string, Vec2D<int>, map_id);	// 引数に対応するグラフィックＩＤを返す

private:
	std::map<map_id, std::vector<graph_info>> mVec;

};