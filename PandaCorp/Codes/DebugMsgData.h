//
// デバッグメッセージを管理する
//

#pragma once

#include <string>
#include <vector>


// シングルトン
class DebugMsgData{

private:
	DebugMsgData() = default;;
	~DebugMsgData();

public:
	DebugMsgData(const DebugMsgData&) = delete;
	DebugMsgData& operator=(const DebugMsgData&) = delete;
	DebugMsgData(DebugMsgData&&) = delete;
	DebugMsgData& operator=(DebugMsgData&&) = delete;

	static DebugMsgData& getInstance(){
		static DebugMsgData obj;
		return obj;
	}

public:
	void setMsg(std::string, std::string);
	std::string getElem(std::string);
	void deleteData();
	std::vector<std::string> getAllMsg();	// 全てのメッセージを取得する

private:
	//int size = 0;
	std::vector<std::pair<std::string, std::string>> mData;

};