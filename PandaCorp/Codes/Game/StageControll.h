//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include <vector>
#include "Mass.h"
#include "Character.h"


class StageControll{

public:
	StageControll(std::string);		// 読み込むjsonファイルを指定する
	~StageControll();
	void update();					// 1フレーム毎の更新処理

private:
	std::vector<std::vector<Mass>> mMass;
	std::vector<Character*> mChara;
	//std::vector<Animation> mAnim;

};