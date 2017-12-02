#include "Stage.h"

#include "Param.h"
#include "InputManager.h"
#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "GraphManager.h"


Stage::Stage(){

	for(int lay = 0; lay < LAYER_NUM; lay++){
		mMass[lay].resize(Param::MASS_NUM.y);
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			mMass[lay][y].resize(Param::MASS_NUM.x);
			for(int x = 0; x < Param::MASS_NUM.x; x++){
				mMass[lay][y][x].gID = -1;
				mMass[lay][y][x].gPath = "";
			}
		}
	}

	Vec2D<int> v1 = {Param::STAGE_FRAME_SIZE.x + 250, 5};
	Vec2D<int> v2 = {Param::WINDOW_SIZE.x, 45};
	mLayerChangeBtn = new Button(v1, v2, "変更");
}


Stage::Stage(std::string path):Stage(){

	// pathで示したjsonファイルからの入力
	try{
		std::ifstream ifs(path);
		picojson::value v;
		std::string err = picojson::parse(v, ifs);
		if(!err.empty()){
			MessageBox(NULL, err.c_str(), "エラー", MB_OK);
			return;
		}

		picojson::array layArr = (picojson::value(v.get<picojson::object>()["Masses"] )).get<picojson::array>();
		int layCnt = 0;
		for(auto layItr = layArr.begin(); layItr != layArr.end(); layItr++){

			int yCnt = 0;
			picojson::array yArr = picojson::value(*layItr).get<picojson::array>();
			for(auto yItr = yArr.begin(); yItr != yArr.end(); yItr++){

				int xCnt = 0;
				picojson::array xArr = picojson::value(*yItr).get<picojson::array>();
				for(auto xItr = xArr.begin(); xItr != xArr.end(); xItr++){
					picojson::object obj = picojson::value(*xItr).get<picojson::object>();
					
					std::string tmp = obj.at("path").get<std::string>();
					mMass[layCnt][yCnt][xCnt].gPath = tmp;

					xCnt++;
				}

				yCnt++;
			}

			layCnt++;
		}

	}
	catch(...){
		MessageBox(NULL, "ファイルが読み込めませんでした(　´_ゝ｀)", "エラー", MB_OK);
	}

	// 読み込んだ各画像パスからグラフィックＩＤを読み込む
	for(int lay = 0; lay < LAYER_NUM; lay++){
		for(int y = 0; y < mMass[lay].size(); y++){
			for(int x = 0; x < mMass[lay][y].size(); x++){
				mMass[lay][y][x].gID = GraphManager::getInstance().checkID(mMass[lay][y][x].gPath, map_id::MASS);
			}
		}
	}
}


Stage::~Stage(){
	delete mLayerChangeBtn;	mLayerChangeBtn = nullptr;
}



// jsonファイルへ現在のステージデータを出力
void Stage::save(std::string path){

	picojson::array parentArr;
	for(int lay = 0; lay < LAYER_NUM; lay++){
		picojson::array layArr;
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			picojson::array yArr;
			for(int x = 0; x < Param::MASS_NUM.x; x++){
				picojson::object xObj;
				xObj.insert( std::make_pair("path", mMass[lay][y][x].gPath) );
				yArr.push_back(picojson::value(xObj));
			}
			layArr.push_back(picojson::value(yArr));
		}
		parentArr.push_back(picojson::value(layArr));
	}
	picojson::object obj;
	obj.emplace(std::make_pair("Masses", parentArr));
	
	picojson::value v = picojson::value(obj);

	std::ofstream ofs(path);
	ofs <<  v;
}


void Stage::draw(){

	// レイヤー順に描画
	for(int lay = 0; lay < LAYER_NUM; lay++){
		for(int y = 0; y < mMass[lay].size(); y++){
			for(int x = 0; x < mMass[lay][y].size(); x++){

				if(mMass[lay][y][x].gID != -1){
					Vec2D<int> gSize;
					GetGraphSize(mMass[lay][y][x].gID, &gSize.x, &gSize.y);

					DrawRotaGraph((x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.x - Param::MASS_SIZE) / 2,
								  (y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.y - Param::MASS_SIZE) / 2,
								  1.0, 0, mMass[lay][y][x].gID, true);

				}
			}
		}
	}

	// 格子
	int lineColor = GetColor(255, 0, 0);
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		DrawLine(0, (y * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.x, (y * Param::MASS_SIZE), lineColor);
	}
	for(int x = 0; x < Param::MASS_NUM.x; x++){
		DrawLine((x * Param::MASS_SIZE), 0, (x * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.y, lineColor);
	}

	DrawFormatString(Param::STAGE_FRAME_SIZE.x + 20, 10, GetColor(255, 0, 0), "レイヤー = %d", mCurrentLayer);
	mLayerChangeBtn->draw();

}


// マスがクリックされたときはログをとってtrueを返す
bool Stage::clickDetectAndAction(){

	// レイヤーの切り替え
	if(mLayerChangeBtn->update()){
		mCurrentLayer++;
		if(mCurrentLayer >= LAYER_NUM){
			mCurrentLayer = 0;
		}
	}

	if(InputManager::getInstance().isPushedMouseLeft()){

		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				Vec2D<int> c1 = {x * Param::MASS_SIZE,			y * Param::MASS_SIZE};
				Vec2D<int> c2 = {(x + 1) * Param::MASS_SIZE,	(y + 1) * Param::MASS_SIZE};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					mClickLog = {x, y};
					return true;
				}
			}
		}

	}

	return false;
}


void Stage::putDataToClickedTile(MassData data){
	mMass[mCurrentLayer][mClickLog.y][mClickLog.x].gID = data.gID;
	mMass[mCurrentLayer][mClickLog.y][mClickLog.x].gPath = data.gPath;
}