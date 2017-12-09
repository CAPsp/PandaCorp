//
// ステージファイルを取り扱うクラス
//

#pragma once


#include <string>
#include <vector>
#include "Mass.h"


class StageFile{

public:
	StageFile(std::string);
	~StageFile() = default;
	std::string read(std::vector<Mass*>&);	// 渡されたvectorにマスオブジェクトを読み込む

private:
	std::string mFilePath;

};