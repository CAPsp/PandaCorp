//
// ゲーム全体を管理している
// メインループを回しているのもこれ
//

#pragma once


#include "BaseScene.h"
#include "ChangeSceneManager.h"


// シングルトンパターン
class MainControll{

private:
	MainControll() = default;
	~MainControll() = default;

public:
	MainControll(const MainControll&) = delete;
	MainControll& operator=(const MainControll&) = delete;
	MainControll(MainControll&&) = delete;
	MainControll& operator=(MainControll&&) = delete;

	static MainControll& getInstance(){
		static MainControll obj;
		return obj;
	}

public:
	void doMainLoop();	// メインループ

private:
	unsigned int mFPS					= 0;		// 計測したFPS値を持つ
	BaseScene* mScene					= nullptr;	// 現在扱ってるシーン
	ChangeSceneManager* mChangeSceneMan = nullptr;	// シーン遷移処理を扱う

};