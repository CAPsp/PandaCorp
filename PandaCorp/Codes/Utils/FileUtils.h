//
// ファイル操作関連の処理をするユーティリティクラス
//

#pragma once


#include <vector>
#include <string>
#include "picojson.h"


class FileUtils{

public:

	// 引数に指定したディレクトリ内のファイルパスを全て取得する
	static std::vector<std::string> readPathInDir(std::string);

	// 引数に指定したディレクトリ以下のファイルパスを全て取得する
	static std::vector<std::string> readPathBelowDir(std::string);

	// 引数に指定したディレクトリ以下のディレクトリパスを全て取得する
	static std::vector<std::string> readDirPathBelowDir(std::string);

	// jsonファイルを開く際の処理
	static std::string openJson(std::string, picojson::value&);

};