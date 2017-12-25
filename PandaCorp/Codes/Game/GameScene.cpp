#include "GameScene.h"

#include "DxLib.h"
#include "GlobalParam.h"
#include "Vec2DUtils.h"
#include "GameSceneParam.h"
#include "GraphManager.h"
#include "picojson.h"
#include "FileUtils.h"
#include "InputManager.h"
#include "SoundManager.h"


StageEndProcess GameScene::sEndProcess;
bool GameScene::sNextCheckClearItemFlag = false;


bool GameScene::begin(){
	sEndProcess.init();
	mStageNameFontHandle = CreateFontToHandle(NULL, 60, 4, DX_FONTTYPE_NORMAL);

	std::string jsonPath = "Stage/" + std::to_string(mStageNum) + ".json";
	mStage = new StageControll(jsonPath);

	mStage->checkExistClearMass(mItemStock);

	// ���t���A�X�R�A��json�t�@�C������ǂݍ���
	picojson::value v;
	std::string err = FileUtils::openJson(jsonPath, v);
	if(err != ""){
		MessageBox(NULL, err.c_str(), "�G���[", MB_OK);
	}
	picojson::array arr = (v.get<picojson::object>()["Date"]).get<picojson::array>();
	mDate.first = (int)(arr.at(0).get<double>());
	mDate.second = (int)(arr.at(1).get<double>());

	mSelectedItemElem = -1;

	PlaySoundMem(SoundManager::getInstance().checkID("BGM/bgm_before.ogg"), DX_PLAYTYPE_BACK);

	return true;
}


scene_sig GameScene::update(){

	// �I�������̏ꍇ�A�`��݂̂��s��
	if(sEndProcess.isActivated()){
		mStage->draw();
		uiDraw();
		return sEndProcess.update();
	}

	if(!mMainSoundStartFlag &&
	   CheckSoundMem(SoundManager::getInstance().checkID("BGM/bgm_before.ogg")) != 1){
		PlaySoundMem(SoundManager::getInstance().checkID("BGM/bgm.ogg"), DX_PLAYTYPE_LOOP);
		mMainSoundStartFlag = true;
	}

	// �A�C�e���I������
	if(InputManager::getInstance().checkPushFrame(KEY_INPUT_X) == 1 && mItemStock.checkSize() > 0){
		mSelectedItemElem = (mSelectedItemElem == -1) ? 0 : -1;
	}
	if(mSelectedItemElem != -1){

		int add = 0;
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_UP) == 1)	{ add = -3; }
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1){ add = 1; }
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_DOWN) == 1)	{ add = 3; }
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1)	{ add = -1; }
		if(0 <= mSelectedItemElem + add && mSelectedItemElem + add < mItemStock.checkSize()){
			mSelectedItemElem += add;
		}

		// �A�C�e���̎g�p
		if(InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1){
			mItemStock.useItem(mSelectedItemElem);
			mSelectedItemElem = -1;
		}

		InputManager::getInstance().deactivate();
	}

	mStage->update();
	// �}�X�̃N���A�`�F�b�N������s��
	if(sNextCheckClearItemFlag){
		mStage->checkExistClearMass(mItemStock);
		sNextCheckClearItemFlag = false;
	}
	
	// ���̗͂L����
	InputManager::getInstance().activate();

	// �`��
	mStage->draw();
	uiDraw();

	mProgressFrame++;

	scene_sig rtn;
	rtn.next = scene_id::NONE;
	return rtn;
}


bool GameScene::end(){
	DeleteFontToHandle(mStageNameFontHandle);
	return true;
}


void GameScene::uiDraw(){

	// �e��p�����[�^��`
	//int spaceWidth = GlobalParam::WINDOW_SIZE.x - GameSceneParam::STAGE_FRAME_SIZE.x;
	std::vector<int> uiNumVec = GraphManager::getInstance().getGraphIDs(std::string(GRAPH_DIR_PATH) + "UI/string/number.png");
	int strGraphWidth = 60;


	// �w�i
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 0,
			GlobalParam::WINDOW_SIZE.x, GlobalParam::WINDOW_SIZE.y,
			GetColor(100, 100, 100), true);

	// ���t�`�� (�Z�Z���Z�Z��)
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

	// ���v�`��i�Z�Z�F�Z�Z�j
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

	// �X�g�b�N���Ă���A�C�e���̕\��
	Vec2D<int> size = {80, 80};
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 3; x++){

			Vec2D<int> p = {GameSceneParam::STAGE_FRAME_SIZE.x + 30 + (x * 110), 260 + (y * 100)};
			
			DrawBox(p.x, p.y, p.x + size.x, p.y + size.y, GetColor(255, 255, 255), true);
			
			int id = mItemStock.checkItemGID(y * 3 + x);
			if(id != -1){
				DrawExtendGraph(p.x, p.y, p.x + size.x, p.y + size.y, id, true);
			}

			// �I�����Ă���A�C�e���̓n�C���C�g
			if(y * 3 + x == mSelectedItemElem){
				DrawBox(p.x, p.y, p.x + size.x, p.y + size.y, GetColor(0, 255, 0), false);
			}
		}
	}

#ifdef _DEBUG
	// UI�̘g��\��
	int frameColor = GetColor(255, 0, 0);
	DrawBox(0, 0, GameSceneParam::STAGE_FRAME_SIZE.x, GameSceneParam::STAGE_FRAME_SIZE.y, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 0, GlobalParam::WINDOW_SIZE.x, GameSceneParam::STAGE_FRAME_SIZE.y, frameColor, false);

	int massColor = GetColor(0, 255, 0);
	for(int y = 0; y < GameSceneParam::MASS_NUM.y; y++){
		for(int x = 0; x < GameSceneParam::MASS_NUM.x; x++){
			DrawBox(x * GameSceneParam::MASS_SIZE, y * GameSceneParam::MASS_SIZE,
				(x + 1) * GameSceneParam::MASS_SIZE, (y + 1) * GameSceneParam::MASS_SIZE,
					massColor, false);
		}
	}

	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 40, GlobalParam::WINDOW_SIZE.x, 100, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 140, GlobalParam::WINDOW_SIZE.x, 200, frameColor, false);
	DrawBox(GameSceneParam::STAGE_FRAME_SIZE.x, 240, GlobalParam::WINDOW_SIZE.x, 660, frameColor, false);
#endif


}


void GameScene::toGameOver(){
	StopSoundMem(SoundManager::getInstance().checkID("BGM/bgm.ogg"));
	PlaySoundMem(SoundManager::getInstance().checkID("gameobera.ogg"), DX_PLAYTYPE_BACK);
	sEndProcess.gameover();
}


void GameScene::toClear(){
	StopSoundMem(SoundManager::getInstance().checkID("BGM/bgm.ogg"));
	PlaySoundMem(SoundManager::getInstance().checkID("clear_se.ogg"), DX_PLAYTYPE_BACK);
	sEndProcess.clear();
}


void GameScene::toStageSelect(){
	sEndProcess.returnStageSelect();
}