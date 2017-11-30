//
// 編集中のステージの情報を持つ
//

#pragma once


#include <vector>
#include <string>


class Stage{

public:
	Stage();											// 何もないステージを開く
	Stage(std::string);									// 引数に指定されたjsonファイルのステージを開く
	void draw();
	void save(std::string);								// 引数に指定されたpathに現状のステージを保存する

private:
	std::vector<std::vector<int>> mMass;
	std::string mName;

};