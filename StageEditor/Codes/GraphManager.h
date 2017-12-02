//
// グラフィックのリソースを管理する
//

#pragma once


#include <string>
#include <map>
#include <vector>


enum map_id{
	MASS,
	CHARA,
	ITEM
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

	std::vector<int> getAllIDFromMap(map_id);	// map_idで指定したMap上にあるすべてのグラフィックIDを返す
	std::string searchPathFromMap(int, map_id);	// 　　　　　〃　　　 　の要素から引数に渡したIDに対応するグラフィックのパスを返す


private:
	std::map<map_id, std::map<std::string, int>> mMap;

};