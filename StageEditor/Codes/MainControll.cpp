#include "MainControll.h"

#include "DxLib.h"
#include "picojson.h"
#include <fstream>
#include "Param.h"


void MainControll::doLoop(){

	picojson::value v;

	std::string err = picojson::parse(v, "{ \"slime\" : 1, \"kawaii\" : 2 }");
	if(!err.empty()){
		MessageBox(NULL, err.c_str(), "error", MB_OK);
	}

	std::ofstream ofs(std::string(GEN_DATA_DIR) + "test.json");

	ofs << v;

	/*
	while(ScreenFlip() == 0 && ProcessMessage() != -1 && ClearDrawScreen() == 0){



	}
	*/

}