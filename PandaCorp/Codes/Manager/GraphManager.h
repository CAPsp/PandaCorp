//
// グラフィックリソースを管理するクラス
// ※ まだ規模の小さいゲームなのでゲーム起動時にリソースを一気に読み込むような設計になってる
// 　 大規模になってきたら修正する必要がある
//

#pragma once


#include <string>
#include <map>


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
	void load();									// リソースを読み込む
	int checkID(std::string);						// 引数に対応するリソースＩＤを返す
	int getDerivGraph(std::string, int, int);	// 大きい画像に対して引数に応じた領域を抜き出す

private:
	std::map<std::string, int> mMap;

};