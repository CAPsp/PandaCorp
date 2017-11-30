//
// 編集中のステージの情報を持つ
//

#pragma once


#include <vector>


class Stage{

public:
	void draw();

private:
	std::vector<std::vector<int>> mMass;

};