//
// グラフィックのリソースを管理する
//

#pragma once


#include <string>
#include <map>
#include <vector>


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
	std::vector<int> getAllMassID();
	std::vector<int> getAllCharaID();
	std::vector<int> getAllItemID();


private:
	std::map<std::string, int> mMassMap;
	std::map<std::string, int> mCharaMap;
	std::map<std::string, int> mItemMap;

};