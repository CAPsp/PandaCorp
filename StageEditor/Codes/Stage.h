//
// 編集中のステージの情報を持つ
//

#pragma once


#include <vector>
#include <string>
#include "MassData.h"
#include "Vec2DUtils.h"
#include "Button.h"
#include "GraphManager.h"
#include "EnemyData.h"


const int GRAPH_LAYER_NUM = 3;


class Stage{

private:
	enum layer_id{
		MASS_0 = 0,
		MASS_1,
		MASS_2,
		MASS_ELEM,
		ITEM,
		CHARA
	};

public:
	Stage();								// 何もないステージを開く
	Stage(std::string);						// 引数に指定されたjsonファイルのステージを開く
	~Stage();
	void save(std::string);					// 引数に指定されたpathに現状のステージを保存する
	void draw();
	bool clickDetectAndAction();			// trueが返したときはMainControllの方にそのマスに置く情報を欲している				
	void putDataToClickedTile(int);			// ログで保存したマスに現在のレイヤー、属性に従った操作を行う

	map_id checkCurrentTab();

private:
	std::vector<std::vector<MassData>> mMass[GRAPH_LAYER_NUM];
	std::string mName;
	Vec2D<int> mPushLog;						// 押されたされたときの情報を持つ
	Button mLayerChangeBtn;						// レイヤーの変更(マス、アイテム、キャラ)
	layer_id mCurrentLayer	= layer_id::MASS_0;
	Vec2D<int> mPlayerPos;
	std::vector<EnemyData> mEnemies;
	int mHoldEnemyElem = -1;					// 現在パトロール順決めで捜査中の敵データ
	std::pair<int, int> mDate = {1, 1};			// ゲームに反映する日付情報を格納

};