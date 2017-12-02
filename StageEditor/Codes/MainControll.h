//
// メインループなどを制御
//

#pragma once


#include "Button.h"
#include "Stage.h"
#include "MaterialTab.h"


// シングルトン
class MainControll{

private:
	MainControll();
	~MainControll();

public:
	MainControll& operator=(const MainControll&) = delete;
	MainControll(const MainControll&) = delete;
	MainControll& operator=(MainControll&&) = delete;
	MainControll(MainControll&&) = delete;

	static MainControll& getInstance(){
		static MainControll obj;
		return obj;
	}

	void doLoop();

private:
	void draw();

private:
	Button* mOpenStageBtn = nullptr;
	Button* mSaveStageBtn = nullptr;
	Stage* mStage = nullptr;
	std::string mFilePath = "";
	MaterialTab* mMaterialTab = nullptr;

};