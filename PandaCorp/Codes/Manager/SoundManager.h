//
// SEやBGMのリソースを管理するクラス
// ※ まだ規模の小さいゲームなのでゲーム起動時にリソースを一気に読み込むような設計になってる
// 　 大規模になってきたら修正する必要がある
//

#pragma once


#include <string>
#include <map>


// ちょっと特殊なシングルトンパターン
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
	void load();				// リソースを読み込む
	int checkID(std::string);	// 引数に対応するリソースＩＤを返す

private:
	std::map<std::string, int> mMap;

};