//
// ゲームシーン上のステージを管理するクラス
//

#pragma once


#include <vector>


class StageControll{

public:
	StageControll();
	~StageControll();
	void draw();		// 描画処理

private:
	std::vector<std::vector<int>> mMass;	// TODO: Mass型を作る
	//std::vector<Character> mChara;
	//std::vector<Animation> mAnim;

};