#include "DebugMsgData.h"

#include <cstdlib>



DebugMsgData::~DebugMsgData(){
	// 領域の解放
	std::vector<std::pair<std::string, std::string>>().swap(mData);
}


// メッセージを登録
void DebugMsgData::setMsg(std::string name, std::string elem){

	// データの検索
	bool flag = false;
	for(auto itr = mData.begin(); itr != mData.end(); itr++){

		// 存在したら更新
		if(itr->first == name){
			itr->second = elem;
			flag = true;
		}
	}

	// 存在しなかったら新しく生成
	if(!flag){
		mData.push_back({name, elem});
	}

	/*
	int i = 0, count = 1;
	for(i = 0; i<size; i++){
		if(data[i].name == name){
			data[i].elem = elem;
			count = 2;
			break;
		}
	}

	try{
		if(count == 1){
			size++;
			int debug = sizeof(DebugMsgData::Data);
			data = (Data*)std::realloc(data, size * sizeof(DebugMsgData::Data));
			//  data[size] = (Data*)std::malloc(sizeof(Data));
			//  size++;

			data[size - 1].name = name;
			data[size - 1].elem = elem;
		}
	}
	catch(std::exception e){
		int cnt = 0;
	}

	int flag = 0;
	*/
}


// 記録されてるメッセージを消去
void DebugMsgData::deleteData(){
	std::vector<std::pair<std::string, std::string>>().swap(mData);

	//for (i=0;i<size;i++) {
	/* 
	std::free(data);
	data = (Data*)std::malloc(0);
	//}
	size = 0;
	*/
}


std::string DebugMsgData::getElem(std::string name){
	
	for(auto itr : mData) {
		if(name == itr.first){
			return itr.second;
		}
	}

	return "";
}


std::vector<std::string> DebugMsgData::getAllMsg(){
	std::vector<std::string> rtn;
	for(auto itr : mData){
		rtn.push_back(itr.second);
	}

	return rtn;
}