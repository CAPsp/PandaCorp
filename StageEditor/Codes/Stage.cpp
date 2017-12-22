#include "Stage.h"

#include "Param.h"
#include "InputManager.h"
#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "GraphManager.h"


Stage::Stage(){

	for(int lay = 0; lay < GRAPH_LAYER_NUM; lay++){
		mMass[lay].resize(Param::MASS_NUM.y);
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			mMass[lay][y].resize(Param::MASS_NUM.x);
		}
	}

	int btnWidth = 180;
	int btnHeight = 35;

	mLayerChangeBtn.changeName("レイヤー変更");
	mLayerChangeBtn.changePos(Param::WINDOW_SIZE.x - btnWidth, 5);
	mLayerChangeBtn.changeSize(btnWidth, btnHeight);
}


Stage::Stage(std::string path):
	Stage(){

	/*
	// pathで示したjsonファイルからの入力
	try{
		std::ifstream ifs(path);
		picojson::value v;
		std::string err = picojson::parse(v, ifs);
		if(!err.empty()){
			MessageBox(NULL, err.c_str(), "エラー", MB_OK);
			return;
		}

		int yCnt = 0;
		picojson::array yArr = (picojson::value(v.get<picojson::object>()["Masses"])).get<picojson::array>();
		for(auto yItr = yArr.begin(); yItr != yArr.end(); yItr++){

			int xCnt = 0;
			picojson::array xArr = picojson::value(*yItr).get<picojson::array>();
			for(auto xItr = xArr.begin(); xItr != xArr.end(); xItr++){
				picojson::object obj = picojson::value(*xItr).get<picojson::object>();
					
				mMass[yCnt][xCnt].gPath[0]	= obj.at("mass_0").get<std::string>();
				mMass[yCnt][xCnt].gPath[1]	= obj.at("mass_1").get<std::string>();
				mMass[yCnt][xCnt].gPath[2]	= obj.at("mass_2").get<std::string>();
				mMass[yCnt][xCnt].pass		= obj.at("pass").get<bool>();
				mMass[yCnt][xCnt].charaPath = obj.at("chara").get<std::string>();
				mMass[yCnt][xCnt].itemPath	= obj.at("item").get<std::string>();

				xCnt++;
			}

			yCnt++;
		}

	}
	catch(...){
		MessageBox(NULL, "ファイルが読み込めませんでした(　´_ゝ｀)", "エラー", MB_OK);
	}

	// 読み込んだ各画像パスからグラフィックＩＤを読み込む
	for(int lay = 0; lay < JSON_LAYER_NUM; lay++){
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){
				mMass[y][x].gID[lay] = GraphManager::getInstance().checkID(mMass[y][x].gPath[lay], map_id::MASS);
			}
		}
	}
	*/
}


Stage::~Stage(){}



// jsonファイルへ現在のステージデータを出力
void Stage::save(std::string path){
	/*
	picojson::array parentArr;
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		picojson::array yArr;
		for(int x = 0; x < Param::MASS_NUM.x; x++){
			picojson::object xObj;
			xObj.insert(std::make_pair("mass_0", mMass[y][x].gPath[0]));
			xObj.insert(std::make_pair("mass_1", mMass[y][x].gPath[1]));
			xObj.insert(std::make_pair("mass_2", mMass[y][x].gPath[2]));
			xObj.insert(std::make_pair("pass", mMass[y][x].pass));
			xObj.insert(std::make_pair("chara", mMass[y][x].charaPath));
			xObj.insert(std::make_pair("item", mMass[y][x].itemPath));
			yArr.push_back(picojson::value(xObj));
		}
		parentArr.push_back(picojson::value(yArr));
	}
	picojson::object obj;
	obj.emplace(std::make_pair("Masses", parentArr));
	
	picojson::value v = picojson::value(obj);

	std::ofstream ofs(path);
	ofs <<  v;
	*/
}


void Stage::draw(){

	// レイヤー順に描画
	for(int lay = 0; lay < GRAPH_LAYER_NUM; lay++){
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				if(mMass[lay][y][x].gID != -1){
					Vec2D<int> gSize;
					GetGraphSize(mMass[lay][y][x].gID, &gSize.x, &gSize.y);

					DrawRotaGraph((x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.x - Param::MASS_SIZE) / 2,
								  (y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.y - Param::MASS_SIZE) / 2,
								  1.0, 0, mMass[lay][y][x].gID, true);

				}

				if(mMass[lay][y][x].gItemID != -1){
					DrawGraph(x * Param::MASS_SIZE, y * Param::MASS_SIZE, mMass[lay][y][x].gItemID, true);
				}
			}
		}
	}

	// 敵とそのパトロール位置を描画
	for(auto itr = mEnemies.begin(); itr != mEnemies.end(); itr++){

		Vec2D<int> gSize;
		GetGraphSize(itr->gID, &gSize.x, &gSize.y);

		DrawRotaGraph(	(itr->patrolVec.at(0).x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.x - Param::MASS_SIZE) / 2,
						(itr->patrolVec.at(0).y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.y - Param::MASS_SIZE) / 2,
						1.0, 0, itr->gID, true);

		int red = 255;
		for(int i = 1; i < (int)(itr->patrolVec.size()); i++){
			DrawLine(itr->patrolVec.at(i - 1).x * Param::MASS_SIZE + Param::MASS_SIZE / 2,
					 itr->patrolVec.at(i - 1).y * Param::MASS_SIZE + Param::MASS_SIZE / 2,
					 itr->patrolVec.at(i).x * Param::MASS_SIZE + Param::MASS_SIZE / 2,
					 itr->patrolVec.at(i).y * Param::MASS_SIZE + Param::MASS_SIZE / 2,
					 GetColor(red, 0, 0));
			red -= (red >= 20) ? 20 : 0;
		}
	}

	// プレイヤーの位置を描画
	DrawCircle(mPlayerPos.x * Param::MASS_SIZE + Param::MASS_SIZE / 2,
			   mPlayerPos.y * Param::MASS_SIZE + Param::MASS_SIZE / 2,
			   Param::MASS_SIZE / 3,
			   GetColor(255, 0, 0), true);
	DrawString(mPlayerPos.x * Param::MASS_SIZE + Param::MASS_SIZE / 4,
			   mPlayerPos.y * Param::MASS_SIZE + Param::MASS_SIZE / 4,
			   "P", GetColor(0, 0, 0));

	// 格子
	int lineColor = GetColor(255, 0, 0);
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		DrawLine(0, (y * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.x, (y * Param::MASS_SIZE), lineColor);
	}
	for(int x = 0; x < Param::MASS_NUM.x; x++){
		DrawLine((x * Param::MASS_SIZE), 0, (x * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.y, lineColor);
	}

	std::string layerStr;
	switch(mCurrentLayer){
		case layer_id::MASS_0:		layerStr = "レイヤー 0";	break;
		case layer_id::MASS_1:		layerStr = "レイヤー 1";	break;
		case layer_id::MASS_2:		layerStr = "レイヤー 2";	break;
		case layer_id::MASS_ELEM:	layerStr = "属性";			break;
		case layer_id::CHARA:		layerStr = "キャラ";		break;
		case layer_id::ITEM:		layerStr = "アイテム";		break;
	}
	DrawString(Param::STAGE_FRAME_SIZE.x + 20, 10, layerStr.c_str(), GetColor(255, 0, 0));
	mLayerChangeBtn.draw();

	// 障害物 or Pass を決めているときは〇、×、△マークを付ける
	if(mCurrentLayer == layer_id::MASS_ELEM){
		lineColor = GetColor(0, 0, 0);
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				int lay;
				for(lay = 0; lay < GRAPH_LAYER_NUM; lay++){

					if(mMass[lay][y][x].elem == mass_elem::NOT_PASS){
						DrawLine(x * Param::MASS_SIZE, y * Param::MASS_SIZE, (x + 1) * Param::MASS_SIZE, (y + 1) * Param::MASS_SIZE, lineColor);
						DrawLine((x + 1) * Param::MASS_SIZE, y * Param::MASS_SIZE, x * Param::MASS_SIZE, (y + 1) * Param::MASS_SIZE, lineColor);
						break;
					}

					if(mMass[lay][y][x].elem == mass_elem::OBSTACLE){
						DrawTriangle(
							x * Param::MASS_SIZE + (Param::MASS_SIZE / 2),	y * Param::MASS_SIZE,
							x * Param::MASS_SIZE,							(y + 1) * Param::MASS_SIZE,
							(x + 1) * Param::MASS_SIZE,						(y + 1) * Param::MASS_SIZE,
							lineColor, false
						);
						break;
					}
				}
				
				if(lay == 3){
					DrawCircle((x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2), (y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2), (Param::MASS_SIZE / 2), lineColor, false);
				}
			}
		}
	}

}


// マスがクリックされたときはログをとってtrueを返す
bool Stage::clickDetectAndAction(){

	// レイヤーの切り替え
	if(mLayerChangeBtn.update()){
		mHoldEnemyElem = -1;
		mCurrentLayer = (mCurrentLayer == layer_id::CHARA) ? layer_id::MASS_0 : layer_id(mCurrentLayer + 1);
	}

	// 右クリックでプレイヤーの位置を変更 or ホールド中の敵を解除
	if(InputManager::getInstance().isPushMouseRight()){

		if(mCurrentLayer == layer_id::CHARA){
			mHoldEnemyElem = -1;
		}
		else{
			for(int y = 0; y < Param::MASS_NUM.y; y++){
				for(int x = 0; x < Param::MASS_NUM.x; x++){

					Vec2D<int> c1 = {x * Param::MASS_SIZE,			y * Param::MASS_SIZE};
					Vec2D<int> c2 = {(x + 1) * Param::MASS_SIZE,	(y + 1) * Param::MASS_SIZE};

					if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){
						mPlayerPos.x = x;
						mPlayerPos.y = y;
					}
				}
			}
		}
	}

	if(InputManager::getInstance().isPushMouseLeft()){

		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				Vec2D<int> c1 = {x * Param::MASS_SIZE,			y * Param::MASS_SIZE};
				Vec2D<int> c2 = {(x + 1) * Param::MASS_SIZE,	(y + 1) * Param::MASS_SIZE};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					// 押し続けて何度も同じマスを上書きしてしまうのを防止
					if(mPushLog.x == x && mPushLog.y == y){
						break;
					}

					mPushLog = {x, y};
					return true;
				}
			}
		}

	}
	else if(InputManager::getInstance().isUpMouseLeft()){	// 押されたときのログは離された瞬間消える
		mPushLog = {-1, -1};
	}

	return false;
}


void Stage::putDataToClickedTile(int id){

	switch(mCurrentLayer){

		case layer_id::MASS_0:
		case layer_id::MASS_1:
		case layer_id::MASS_2:
			mMass[(int)mCurrentLayer][mPushLog.y][mPushLog.x].gID = id;
			
			// そのマスの属性を全て消す
			for(int lay = 0; lay < GRAPH_LAYER_NUM; lay++){
				mMass[lay][mPushLog.y][mPushLog.x].elem = mass_elem::NORMAL;
			}
			break;

		case layer_id::MASS_ELEM:		// グラフィックレイヤー的に一番上に存在するグラフィックに適用する
			for(int lay = GRAPH_LAYER_NUM - 1; lay >= 0; lay--){
				if(mMass[lay][mPushLog.y][mPushLog.x].gID != -1){

					if(mMass[lay][mPushLog.y][mPushLog.x].elem == mass_elem::OBSTACLE){
						mMass[lay][mPushLog.y][mPushLog.x].elem = mass_elem::NORMAL;
					}
					else{
						mMass[lay][mPushLog.y][mPushLog.x].elem = mass_elem(mMass[lay][mPushLog.y][mPushLog.x].elem + 1);
					}
					break;
				}
			}
			break;

		case layer_id::CHARA:	// パトロール決め中かどうかで分岐する
			if(mHoldEnemyElem != -1){
				mEnemies.at(mHoldEnemyElem).patrolVec.push_back(Vec2D<int>(mPushLog.x, mPushLog.y));
			}
			else{
				if(id == -1){
					for(auto itr = mEnemies.begin(); itr != mEnemies.end(); itr++){
						if(itr->patrolVec.at(0).x == mPushLog.x && itr->patrolVec.at(0).y == mPushLog.y){
							mEnemies.erase(itr);
							break;
						}
					}
				}
				else{
					EnemyData tmp;
					tmp.gID = id;
					tmp.patrolVec.push_back(Vec2D<int>(mPushLog.x, mPushLog.y));
					mEnemies.push_back(tmp);
					mHoldEnemyElem = (int)(mEnemies.size()) - 1;
				}
			}
			break;
		case layer_id::ITEM:
			mMass[GRAPH_LAYER_NUM - 1][mPushLog.y][mPushLog.x].gItemID = id;
			break;
	}

}

map_id Stage::checkCurrentTab(){
	if(mCurrentLayer == layer_id::ITEM)			{ return map_id::ITEM; }
	else if(mCurrentLayer == layer_id::CHARA)	{ return map_id::CHARA; }
	return map_id::MASS;
}