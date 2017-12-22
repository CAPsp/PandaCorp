#include "MaterialTab.h"

#include "DxLib.h"
#include "Param.h"
#include "InputManager.h"


MaterialTab::MaterialTab(map_id id){

	mMassGraphID = GraphManager::getInstance().getAllIDFromVec(id);
	mMassGraphID.insert(mMassGraphID.begin(), -1);	// 消しゴム用の空マス

	mOrigin = {Param::STAGE_FRAME_SIZE.x, 100};

	// マスが何個置けるかを計算
	int x, y;
	for(y = 0; (y * Param::MASS_SIZE) < Param::RIGHT_FRAME_SIZE.y; y++);
	for(x = 0; (x * Param::MASS_SIZE) < Param::RIGHT_FRAME_SIZE.x; x++);
	mMassNum = {x, y};
}


void MaterialTab::clickDetectAndAction(){

	// クリックされたときのマスグラフィックを選択状態とする
	if(InputManager::getInstance().isUpMouseLeft()){
		for(int y = 0; y < mMassNum.y; y++){
			for(int x = 0; x < mMassNum.y; x++){

				Vec2D<int> c1 = { mOrigin.x + (x * Param::MASS_SIZE),		mOrigin.y + (y * Param::MASS_SIZE)};
				Vec2D<int> c2 = { mOrigin.x + ((x + 1) * Param::MASS_SIZE), mOrigin.y + ((y + 1) * Param::MASS_SIZE)};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					// mMassGraphIDの何番目に入ってるものかを逆算
					int elem = (y * mMassNum.x) + x;
					if(elem < mMassGraphID.size()){
						mSelectDataGID = mMassGraphID[elem];
					}
				}
			}
		}

	}

}


void MaterialTab::draw(){

	// マスグラフィック
	std::vector<int>::iterator itr = mMassGraphID.begin();
	for(int y = 0; y < mMassNum.y; y++){
		for(int x = 0; x < mMassNum.x; x++){
			
			if(itr != mMassGraphID.end()){

				// 選択されていた場合はハイライト
				if(mSelectDataGID == (*itr)){
					DrawBox(mOrigin.x + (x * Param::MASS_SIZE),
							mOrigin.y + (y * Param::MASS_SIZE),
							mOrigin.x + ((x + 1) * Param::MASS_SIZE),
							mOrigin.y + ((y + 1) * Param::MASS_SIZE),
							GetColor(255, 0, 0),
							true);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					
				}

				// グラフィックの下部分(40×40)だけが見えるように描画
				Vec2D<int> gSize;
				GetGraphSize(*itr, &(gSize.x), &(gSize.y));
				DrawRectGraph(mOrigin.x + (x * Param::MASS_SIZE),
							  mOrigin.y + (y * Param::MASS_SIZE),
							  gSize.x - Param::MASS_SIZE,
							  gSize.y - Param::MASS_SIZE,
							  Param::MASS_SIZE,
							  Param::MASS_SIZE,
							  (*itr),
							  false,
							  false);

				if(mSelectDataGID == (*itr)){
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
				}

				itr++;
			}
			else{
				// 対応するマスが存在しない場合は青く染める
				DrawBox(mOrigin.x + (x * Param::MASS_SIZE),
						mOrigin.y + (y * Param::MASS_SIZE),
						mOrigin.x + ((x+1) * Param::MASS_SIZE),
						mOrigin.y + ((y+1) * Param::MASS_SIZE),
						GetColor(0, 0, 255),
						true);
			}

		}
	}

	// 格子
	int lineColor = GetColor(0, 255, 0);
	DrawBox(mOrigin.x, mOrigin.y, Param::WINDOW_SIZE.x, Param::WINDOW_SIZE.y, lineColor, false);
	for(int x = 1; x < mMassNum.x; x++){
		DrawLine(mOrigin.x + (x * Param::MASS_SIZE),
				 mOrigin.y,
				 mOrigin.x + (x * Param::MASS_SIZE),
				 Param::RIGHT_FRAME_SIZE.y,
				 lineColor);
	}

	for(int y = 1; y < mMassNum.y; y++){
		DrawLine(mOrigin.x,
				 mOrigin.y + (y * Param::MASS_SIZE),
				 Param::WINDOW_SIZE.x,
				 mOrigin.y + (y * Param::MASS_SIZE),
				 lineColor);
	}
}