//
// メインループなどを制御
//

#pragma once


// シングルトン
class MainControll{

private:
	MainControll() = default;
	~MainControll() = default;

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



};