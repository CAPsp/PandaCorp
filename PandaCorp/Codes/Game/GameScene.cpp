#include "GameScene.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "GameSceneParam.h"
#include "GraphManager.h"
#include "picojson.h"
#include "FileUtils.h"


StageEndProcess GameScene::sEndProcess;


bool GameScene::begin(){
	sEndProcess.init();
	mStageNameFontHandle = CreateFontToHandle(NULL, 60, 4, DX_FONTTYPE_NORMAL);

	// デバッグ用
	std::string jsonPath = "Stage/test.json";
	mStage = new StageControll(jsonPath);

	// 日付情報、スコアをjsonファイルから読み込む
	picojson::value v;
	std::string err = FileUtils::openJson(jsonPath, v);
	if(err != ""){
		MessageBox(NULL, err.c_str(), "エラー", MB_OK);
	}
	picojson::array arr = (v.get<picojson::object>()["Date"]).get<picojson::array>();
	mDate.first = (int)(arr.at(0).get<double>());
	mDate.second = (int)(arr.at(1).get<double>());

	return true;
}


scene_sig GameScene::update(){

	mStage->update();

	// UI部分描画
	uiDraw();

#ifdef _DEBUG
	// UIの枠を表示
	int frameColor = GetColor(255, 0, 0);
	DrawBox(0,									0,	GameSceneParam::STAGE_FRAME_SIZE.x, GameSceneParam::STAGE_FRAME_SIZE.y, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 0,	GlobalParam::WINDOW_SIZE.x,			GameSceneParam::STAGE_FRAME_SIZE.y, frameColor, false);

	int massColor = GetColor(0, 255, 0);
	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		for(int x = 0; x < GameSceneParam::MASS_NUM.x; x++){
			DrawBox( x * GameSceneParam::MASS_SIZE, y * GameSceneParam::MASS_SIZE,
					 (x + 1) * GameSceneParam::MASS_SIZE, (y + 1) * GameSceneParam::MASS_SIZE,
					 massColor, false);
		}
	}

	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 40, GlobalParam::WINDOW_SIZE.x, 100, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 140, GlobalParam::WINDOW_SIZE.x, 200, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 240, GlobalParam::WINDOW_SIZE.x, 660, frameColor, false);
#endif

	mProgressFrame++;

	return sEndProcess.update();	// ゲームオーバーやクリア処理をしてないときはシーンを切り替えないようにしてる
}


bool GameScene::end(){
	DeleteFontToHandle(mStageNameFontHandle);
	return true;
}


void GameScene::uiDraw(){

	// 各種パラメータ定義
	//int spaceWidth = GlobalParam::WINDOW_SIZE.x - GameSceneParam::STAGE_FRAME_SIZE.x;
	std::vector<int> uiNumVec = GraphManager::getInstance().getGraphIDs(std::string(GRAPH_DIR_PATH) + "UI/string/number.png");
	int strGraphWidth = 60;


	// 背景
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 0,
			GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y,
			GetColor(100, 100, 100), true);

	// 日付描画 (〇〇月〇〇日)
	int dateG[6] = {
		uiNumVec.at(mDate.first / 10),
		uiNumVec.at(mDate.first % 10),
		uiNumVec.at(11),
		uiNumVec.at(mDate.second / 10),
		uiNumVec.at(mDate.second % 10),
		uiNumVec.at(12)};
	for(int i = 0; i < 6; i++){
		DrawGraph(GameSceneParam::STAGE_FRAME_SIZE.x + (strGraphWidth * i), 40, dateG[i], true);
	}

	// 時計描画（〇〇：〇〇）
	int hour	= ((mProgressFrame / GlobalParam::FPS + GameSceneParam::CLOSING_TIME_MINUTE) / 60 + GameSceneParam::CLOSING_TIME_HOUR) % 24;
	int minute	=  (mProgressFrame / GlobalParam::FPS + GameSceneParam::CLOSING_TIME_MINUTE) % 60;
	int timeG[5] = {
		uiNumVec.at(hour / 10),
		uiNumVec.at(hour % 10),
		uiNumVec.at(10),
		uiNumVec.at(minute / 10),
		uiNumVec.at(minute % 10)};
	for(int i = 0; i < 5; i++){
		DrawGraph(GameSceneParam::STAGE_FRAME_SIZE.x + (strGraphWidth * i) + 30, 140, timeG[i], true);
	}

	// ストックしているアイテムの表示
	Vec2D<int> size = {80, 80};
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 3; x++){

			Vec2D<int> p = {GameSceneParam::STAGE_FRAME_SIZE.x + 30 + (x * 110), 260 + (y * 100)};
			
			DrawBox(p.x, p.y, p.x + size.x, p.y + size.y, GetColor(255, 255, 255), true);
			
			int id = mItemStock.checkItemGID(y * 3 + x);
			if(id != -1){
				DrawExtendGraph(p.x, p.y, p.x + size.x, p.y + size.y, id, true);
			}
		}
	}

}
