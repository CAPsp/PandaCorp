#include "StageSelectScene.h"

#include"InputManager.h"
#include "DxLib.h"
#include "SoundManager.h"

#define StageNum 6 //ステージ数
#define PI    3.1415926535897932384626433832795f

//グローバル変数宣言
int stage_select = 1;
int step = 0;
int select_decide = 0;
int Fontstageselect; //ステージ選択で使っているフォント
int Stageselect_Cursor;

//セーブデータから読み込んだ値を保存する変数
FILE *fp_hiscore;
int hiscore[StageNum] = { 0, 0, 0, 0, 0, 0 };//ハイスコア保存用
int stageappear = 1;//現在出現しているステージの数を保存

//begin, end関数の代わりの処理をするための変数　それぞれ移植したら削除
int _begin = 0;
int _end = 0;


scene_sig StageSelectScene::update() {
	scene_sig rtn;

	int i;
	int go_next = 0;

	//begin関数の代わり 移植したら削除
	if (_begin == 0) {

		//begin関数に入れる予定の処理
		Fontstageselect = CreateFontToHandle(NULL, 40, 5, DX_FONTTYPE_NORMAL);
		SetTransColor(255, 255, 255);
		Stageselect_Cursor = LoadGraph("test_cursor.png");

		//以下データ読み込みのテスト用コード

		//テスト　データ書き込み
		/*
		fopen_s(&fp_hiscore, "test_hi.dat", "wb");
		if (fp_hiscore == NULL)
		{
			for (i = 0; i < StageNum; i++) {
				hiscore[i] = 0;
			}
		}
		else {
			fwrite(&stageappear, sizeof(int), 1, fp_hiscore);
			for (i = 0; i < StageNum; i++) {
				fwrite(&hiscore[i], sizeof(int), 1, fp_hiscore);
			}
		}
		*/

		//テスト　データ読み込み

		fopen_s(&fp_hiscore, "test_hi.dat", "rb");

		if (fp_hiscore == NULL)
		{
			for (i = 0; i < StageNum; i++) {
				hiscore[i] = 0;
			}
		}
		else {
			fread(&stageappear, sizeof(int), 1, fp_hiscore);
			for (i = 0; i < StageNum; i++) {
				fread(&hiscore[i], sizeof(int), 1, fp_hiscore);
			}
		}

		fclose(fp_hiscore);

		//↑ここまでテスト用コード

		_begin = 1;
	}

	//ステージ選択の描写処理

	//上部の処理
	//※ステージ数変えるときに調整必須※
	for (i = 1; i <= stageappear; i++) {
		if (i == stage_select) {
			DrawBox(150 + (i - 1) * 170, 80, 150 + (i - 1) * 170 + 130, 260, GetColor(255, 255, 255), TRUE);

			//カーソルの描写
			DrawGraph(150 + (i - 1) * 170 + 45, 30, Stageselect_Cursor, TRUE);
		}
		else {
			DrawBox(150 + (i - 1) * 170, 80, 150 + (i - 1) * 170 + 130, 260, GetColor(128, 128, 128), TRUE);
		}
		DrawFormatStringToHandle(150 + 55 + (i - 1) * 170, 160, GetColor(0, 0, 0), Fontstageselect, "%d", i);
	}

	//下部の処理
	DrawFormatStringToHandle(156, 520, GetColor(255, 255, 255), Fontstageselect, "Stage%d", stage_select);
	DrawStringToHandle(994, 492, "ハイスコア", GetColor(255, 255, 255), Fontstageselect);
	DrawFormatStringToHandle(1009, 566, GetColor(255, 255, 255), Fontstageselect, "%08d", hiscore[stage_select - 1]);

	DrawBox(346, 320, 934, 656, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(406, 420, "マップ全体像とか\nステージの情報を\n表示するところ", GetColor(0, 0, 0), Fontstageselect);

	//ステージ選択に関する処理
	if (step == 0) {

		//ステージ選択カーソル処理
		//左キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (stage_select > 1) {
				stage_select--;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);

		}

		//右キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (stage_select < stageappear) {
				stage_select++;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}
		//エンターキーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1) {
			step = 1;

			PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
		}
	}

	//選択後　確認の処理
	else if (step == 1) {

		//確認ボタンの描写
		DrawBox(246, 134, 1034, 586, GetColor(255, 255, 0), TRUE);
		DrawBox(256, 144, 1024, 576, GetColor(255, 255, 255), TRUE);
		DrawStringToHandle(380, 204, "このステージで遊びますか？", GetColor(0, 0, 0), Fontstageselect);
		DrawStringToHandle(380, 484, "はい", GetColor(0, 0, 0), Fontstageselect);
		DrawStringToHandle(830, 484, "いいえ", GetColor(0, 0, 0), Fontstageselect);

		//カーソルの描写
		DrawRotaGraph2(360 + select_decide * 450, 504, 20, 20, 1.0, 2 * PI * 3 / 4, Stageselect_Cursor, TRUE);

		//ステージ選択カーソル処理
		//左キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (select_decide != 0) {
				select_decide = 0;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}

		//右キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (select_decide != 1) {
				select_decide = 1;
			}

			PlaySoundMem(SoundManager::getInstance().checkID("select02.ogg"), DX_PLAYTYPE_BACK);
		}
		//エンターキーの処理
		//はいを選んだらステージ画面へ進む　いいえを選んだらステージ選択の処理へ戻る
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_Z) == 1) {
			if (select_decide == 0) {
				go_next = 1;

				PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			}
			else {
				step = 0;
				select_decide = 0;

				PlaySoundMem(SoundManager::getInstance().checkID("selectse.ogg"), DX_PLAYTYPE_BACK);
			}
		}
	}

	if (go_next == 0) {
		rtn.next = scene_id::NONE;
	}
	else
	{
		stage_select = 1;
		step = 0;
		select_decide = 0;
		rtn.next = scene_id::GAME;
		rtn.meta = stage_select; // 1 ～ StageNum の値を返す
	}

	return rtn;
}

// trueを返すまで beginの処理を継続する
bool StageSelectScene::begin() {

	return true;
}

// trueを返すまで beginの処理を継続する
bool StageSelectScene::end() {
	return true;
}
