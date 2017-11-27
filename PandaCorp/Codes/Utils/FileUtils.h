//
// ファイル操作関連の処理をするユーティリティクラス
//

#pragma once


#include <vector>
#include <string>


class FileUtils{

public:

	// 引数に指定したディレクトリ内のファイルパスを全て取得する
	static std::vector<std::string> readPathInDir(std::string);

	// 引数に指定したディレクトリ以下のファイルパスを全て取得する
	static std::vector<std::string> readPathBelowDir(std::string);

};