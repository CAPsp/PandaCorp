//
// 編集中のステージの情報を持つ
//

#pragma once


#include <vector>
#include <string>
#include "MassData.h"
#include "Vec2DUtils.h"
#include "Button.h"


class Stage{

private:
	enum layer_id{
		MASS_0,
		MASS_1,
		MASS_2,
		PASS,
		CHARA,
		ITEM
	};

public:
	Stage();								// 何もないステージを開く
	Stage(std::string);						// 引数に指定されたjsonファイルのステージを開く
	~Stage();
	void save(std::string);					// 引数に指定されたpathに現状のステージを保存する
	void draw();
	bool clickDetectAndAction();			// trueが返したときはMainControllの方にそのマスに置く情報を欲している				
	void putDataToClickedTile(MassData);	// ログで保存したマスに引数のデータを置く

private:
	std::vector<std::vector<MassData>> mMass;
	std::string mName;
	Vec2D<int> mPushLog;		// 押されたされたときの情報を持つ
	Button *mLayerChangeBtn = nullptr;
	layer_id mCurrentLayer = layer_id::MASS_0;

};