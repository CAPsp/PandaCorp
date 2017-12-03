#include "StageControll.h"

#include "GameSceneParam.h"
#include "DxLib.h"
#include "GraphManager.h"
#include <fstream>
#include "picojson.h"
#include "Player.h"


StageControll::StageControll(std::string jsonPath){
	
	mMass.resize(GameSceneParam::MASS_NUM.y);
	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		mMass[y].resize(GameSceneParam::MASS_NUM.x);
	}

	// jsonファイルの仕様はエディターと整合性を保つ必要があるため変更される可能性がある
	try{
		std::ifstream ifs(jsonPath);
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

				mMass[yCnt][xCnt].mGID[0] = GraphManager::getInstance().checkID(obj.at("mass_0").get<std::string>());
				mMass[yCnt][xCnt].mGID[1] = GraphManager::getInstance().checkID(obj.at("mass_1").get<std::string>());
				mMass[yCnt][xCnt].mGID[2] = GraphManager::getInstance().checkID(obj.at("mass_2").get<std::string>());
				mMass[yCnt][xCnt].mPass = obj.at("pass").get<bool>();
				
				//mMass[yCnt][xCnt].charaPath = obj.at("chara").get<std::string>();
				//mMass[yCnt][xCnt].itemPath = obj.at("item").get<std::string>();

				xCnt++;
			}

			yCnt++;
		}

	}
	catch(...){
		MessageBox(NULL, "ステージファイルが読み込めませんでした(　´_ゝ｀)", "エラー", MB_OK);
	}

	mChara.push_back(new Player());
}


StageControll::~StageControll(){}


void StageControll::update(){

	// レイヤー順にマスを描画
	int mSize = GameSceneParam::MASS_SIZE;
	for(int lay = 0; lay < GameSceneParam::MASS_GRAPH_LAYER_NUM; lay++){
		for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
			for(int x = 0; x < GameSceneParam::MASS_NUM.x; x++){

				if(mMass[y][x].mGID[lay] != -1){
					Vec2D<int> gSize;
					GetGraphSize(mMass[y][x].mGID[lay], &gSize.x, &gSize.y);

					DrawRotaGraph(	(x * mSize) + (mSize / 2) - (gSize.x - mSize) / 2,
									(y * mSize) + (mSize / 2) - (gSize.y - mSize) / 2,
									1.0, 0, mMass[y][x].mGID[lay], true);

				}
			}
		}
	}

	// キャラの処理
	for(auto chara : mChara){
		chara->update();
	}

}