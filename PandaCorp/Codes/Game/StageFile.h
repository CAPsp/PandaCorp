//
// ステージファイルを取り扱うクラス
//

#pragma once


#include <string>
#include <vector>
#include "GameObj.h"
#include "GameObjContainer.h"


class StageFile{

public:
	StageFile(std::string);
	~StageFile() = default;
	std::string read(GameObjContainer*);	// 渡されたvectorにマスオブジェクトを読み込む

private:
	std::string mFilePath;

};