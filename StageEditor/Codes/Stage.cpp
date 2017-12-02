#include "Stage.h"

#include "Param.h"
#include "InputManager.h"
#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "GraphManager.h"


Stage::Stage(){

	mMass.resize(Param::MASS_NUM.y);
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		mMass[y].resize(Param::MASS_NUM.x);
	}

	Vec2D<int> v1 = {Param::STAGE_FRAME_SIZE.x + 250, 5};
	Vec2D<int> v2 = {Param::WINDOW_SIZE.x, 45};
	mLayerChangeBtn = new Button(v1, v2, "�ύX");
}


Stage::Stage(std::string path):Stage(){

	// path�Ŏ�����json�t�@�C������̓���
	try{
		std::ifstream ifs(path);
		picojson::value v;
		std::string err = picojson::parse(v, ifs);
		if(!err.empty()){
			MessageBox(NULL, err.c_str(), "�G���[", MB_OK);
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
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł���(�@�L_�T�M)", "�G���[", MB_OK);
	}

	// �ǂݍ��񂾊e�摜�p�X����O���t�B�b�N�h�c��ǂݍ���
	for(int lay = 0; lay < JSON_LAYER_NUM; lay++){
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){
				mMass[y][x].gID[lay] = GraphManager::getInstance().checkID(mMass[y][x].gPath[lay], map_id::MASS);
			}
		}
	}
	
}


Stage::~Stage(){
	delete mLayerChangeBtn;	mLayerChangeBtn = nullptr;
}



// json�t�@�C���֌��݂̃X�e�[�W�f�[�^���o��
void Stage::save(std::string path){

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
}


void Stage::draw(){

	// ���C���[���ɕ`��
	for(int lay = 0; lay < JSON_LAYER_NUM; lay++){
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				if(mMass[y][x].gID[lay] != -1){
					Vec2D<int> gSize;
					GetGraphSize(mMass[y][x].gID[lay], &gSize.x, &gSize.y);

					DrawRotaGraph((x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.x - Param::MASS_SIZE) / 2,
								  (y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2) - (gSize.y - Param::MASS_SIZE) / 2,
								  1.0, 0, mMass[y][x].gID[lay], true);

				}
			}
		}
	}

	// �i�q
	int lineColor = GetColor(255, 0, 0);
	for(int y = 0; y < Param::MASS_NUM.y; y++){
		DrawLine(0, (y * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.x, (y * Param::MASS_SIZE), lineColor);
	}
	for(int x = 0; x < Param::MASS_NUM.x; x++){
		DrawLine((x * Param::MASS_SIZE), 0, (x * Param::MASS_SIZE), Param::STAGE_FRAME_SIZE.y, lineColor);
	}

	std::string layerStr;
	switch(mCurrentLayer){
		case layer_id::MASS_0:	layerStr = "���C���[ 0";	break;
		case layer_id::MASS_1:	layerStr = "���C���[ 1";	break;
		case layer_id::MASS_2:	layerStr = "���C���[ 2";	break;
		case layer_id::PASS:	layerStr = "�ʂ�邩";		break;
		case layer_id::CHARA:	layerStr = "�L����";		break;
		case layer_id::ITEM:	layerStr = "�A�C�e��";		break;
	}
	DrawString(Param::STAGE_FRAME_SIZE.x + 20, 10, layerStr.c_str(), GetColor(255, 0, 0));
	mLayerChangeBtn->draw();

	// �ʂ�邩�ǂ��������߂Ă���Ƃ������Z�A�~�}�[�N��t����
	if(mCurrentLayer == layer_id::PASS){
		lineColor = GetColor(0, 0, 0);
		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				if(mMass[y][x].pass){
					DrawCircle((x * Param::MASS_SIZE) + (Param::MASS_SIZE / 2), (y * Param::MASS_SIZE) + (Param::MASS_SIZE / 2), (Param::MASS_SIZE / 2), lineColor, false);
				}
				else{
					DrawLine(x * Param::MASS_SIZE, y * Param::MASS_SIZE, (x + 1) * Param::MASS_SIZE, (y + 1) * Param::MASS_SIZE, lineColor);
					DrawLine((x + 1) * Param::MASS_SIZE, y * Param::MASS_SIZE, x * Param::MASS_SIZE, (y + 1) * Param::MASS_SIZE, lineColor);
				}
			}
		}
	}

}


// �}�X���N���b�N���ꂽ�Ƃ��̓��O���Ƃ���true��Ԃ�
bool Stage::clickDetectAndAction(){

	// ���C���[�̐؂�ւ�
	if(mLayerChangeBtn->update()){
		switch(mCurrentLayer){
			case layer_id::MASS_0:	mCurrentLayer = layer_id::MASS_1;		break;
			case layer_id::MASS_1:	mCurrentLayer = layer_id::MASS_2;		break;
			case layer_id::MASS_2:	mCurrentLayer = layer_id::PASS;			break;
			case layer_id::PASS:	mCurrentLayer = layer_id::CHARA;		break;
			case layer_id::CHARA:	mCurrentLayer = layer_id::ITEM;			break;
			case layer_id::ITEM:	mCurrentLayer = layer_id::MASS_0;		break;
		}
	}

	if(InputManager::getInstance().isPushMouseLeft()){

		for(int y = 0; y < Param::MASS_NUM.y; y++){
			for(int x = 0; x < Param::MASS_NUM.x; x++){

				Vec2D<int> c1 = {x * Param::MASS_SIZE,			y * Param::MASS_SIZE};
				Vec2D<int> c2 = {(x + 1) * Param::MASS_SIZE,	(y + 1) * Param::MASS_SIZE};

				if(InputManager::getInstance().existCursorInArea(c1.x, c1.y, c2.x, c2.y)){

					// ���������ĉ��x�������}�X���㏑�����Ă��܂��̂�h�~
					if(mPushLog.x == x && mPushLog.y == y){
						break;
					}

					if(mCurrentLayer == layer_id::PASS){
						mMass[y][x].pass = !mMass[y][x].pass;
					}
					mPushLog = {x, y};
					return true;
				}
			}
		}

	}
	else if(InputManager::getInstance().isUpMouseLeft()){	// �N���b�N���O�͗����ꂽ�u�ԏ�����
		mPushLog = {-1, -1};
	}

	return false;
}


// �}�X�̃O���t�B�b�N�p�X��ID��0�Ԗڂ̗v�f�ɓ���
void Stage::putDataToClickedTile(MassData data){

	switch(mCurrentLayer){
		case layer_id::MASS_0:
			mMass[mPushLog.y][mPushLog.x].gID[0]	= data.gID[0];
			mMass[mPushLog.y][mPushLog.x].gPath[0]	= data.gPath[0];
			break;
		case layer_id::MASS_1:
			mMass[mPushLog.y][mPushLog.x].gID[1]	= data.gID[0];
			mMass[mPushLog.y][mPushLog.x].gPath[1]	= data.gPath[0];
			break;
		case layer_id::MASS_2:
			mMass[mPushLog.y][mPushLog.x].gID[2]	= data.gID[0];
			mMass[mPushLog.y][mPushLog.x].gPath[2]	= data.gPath[0];
			break;
		case layer_id::CHARA:
			mMass[mPushLog.y][mPushLog.x].charaPath	= data.charaPath;
			break;
		case layer_id::ITEM:
			mMass[mPushLog.y][mPushLog.x].itemPath	= data.itemPath;
			break;
	}

}