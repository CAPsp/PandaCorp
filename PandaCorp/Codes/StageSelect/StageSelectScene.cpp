#include "StageSelectScene.h"

#include"InputManager.h"
#include "DxLib.h"

#define StageNum 6 //ステージ数

//グローバル変数宣言
int stage_select = 0;
int step = 0;
int select_decide = 0;

scene_sig StageSelectScene::update() {
	scene_sig rtn;

	int i;
	int go_next = 0;

	DrawFormatString(200, 600, GetColor(255, 255, 255), "stage_select: %d", stage_select);


	//ステージ選択の描写処理
	//※ステージ数変えるときに調整必須※
	for (i = 0; i < StageNum; i++) {
		if (i == stage_select) {
			DrawBox(150 + i * 170, 80, 150 + i * 170 + 130, 260, GetColor(255, 255, 255), TRUE);
		}
		else {
			DrawBox(150 + i * 170, 80, 150 + i * 170 + 130, 260, GetColor(128, 128, 128), TRUE);
		}
		DrawFormatString(150 + 65 + i * 170, 170, GetColor(0, 0, 0), "%d", i);
	}

	//ステージ選択に関する処理
	if (step == 0) {

		//ステージ選択カーソル処理
		//左キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (stage_select > 0) {
				stage_select--;
			}
		}

		//右キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (stage_select < StageNum - 1) {
				stage_select++;
			}
		}
		//エンターキーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RETURN) == 1) {
			step = 1;
		}
	}

	//選択後　確認の処理
	else if (step == 1) {

		//確認ボタンの描写
		DrawBox(246, 134, 1034, 586, GetColor(255, 255, 0), TRUE);
		DrawBox(256, 144, 1024, 576, GetColor(255, 255, 255), TRUE);
		DrawString(530, 204,"このステージで遊びますか？", GetColor(0, 0, 0));
		DrawString(360, 404, "はい", GetColor(0, 0, 0));
		DrawString(830, 404, "いいえ", GetColor(0, 0, 0));

		//カーソルの描写
		DrawString(340 + select_decide*470, 404, "→", GetColor(0, 0, 0));

		//ステージ選択カーソル処理
		//左キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_LEFT) == 1) {
			if (select_decide != 0) {
				select_decide = 0;
			}
		}

		//右キーの処理
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RIGHT) == 1) {
			if (select_decide != 1) {
				select_decide = 1;
			}
		}
		//エンターキーの処理
		//はいを選んだらステージ画面へ進む　いいえを選んだらステージ選択の処理へ戻る
		if (InputManager::getInstance().checkPushFrame(KEY_INPUT_RETURN) == 1) {
			if (select_decide == 0) {
				go_next = 1;
			}
			else {
				step = 0;
				select_decide = 0;
			}
		}
	}

	if (go_next == 0) {
		rtn.next = scene_id::NONE;
	}
	else {
		rtn.next = scene_id::GAME;
		rtn.meta = stage_select+1; // 1 ～ StageNum の値を返す
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
