//
// グラフィックリソースを管理するクラス
// ※ まだ規模の小さいゲームなのでゲーム起動時にリソースを一気に読み込むような設計になってる
// 　 大規模になってきたら修正する必要がある
//

#pragma once


#include <string>
#include <map>
#include <vector>
#include "Vec2DUtils.h"


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
	void clear();
	void load();								// リソースを読み込む
	int checkID(std::string, Vec2D<int>);		// 引数に対応するリソースＩＤを返す
	std::vector<int> getGraphIDs(std::string);	// 引数に対応するパス内の画像群を返す

private:
	std::map<std::string, std::vector< std::pair<Vec2D<int>, int> >> mDatabase;

};