#include "FileUtils.h"

#include <Windows.h>
#include <fstream>



std::vector<std::string> FileUtils::readPathInDir(std::string dir_path){

	std::vector<std::string> vec;

	WIN32_FIND_DATA win32fd;
	HANDLE handle = FindFirstFile((dir_path + "\\*").c_str(), &win32fd);
	if(handle == INVALID_HANDLE_VALUE){
		return vec;
	}

	do{
		// ディレクトリなら飛ばす
		if(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){}
		else{
			vec.push_back(dir_path + win32fd.cFileName);
		}
	} while(FindNextFile(handle, &win32fd));

	FindClose(handle);

	return vec;
}


std::vector<std::string> FileUtils::readPathBelowDir(std::string dir_path){

	std::vector<std::string> vec;

	WIN32_FIND_DATA win32fd;
	HANDLE handle = FindFirstFile((dir_path + "\\*").c_str(), &win32fd);
	if(handle == INVALID_HANDLE_VALUE){
		return vec;
	}

	do{
		// ディレクトリなら再帰的に探索
		if((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		   std::string(win32fd.cFileName) != "." &&
		   std::string(win32fd.cFileName) != ".."){
			std::vector<std::string> tmp = readPathBelowDir(dir_path + win32fd.cFileName + "/");
			std::copy(tmp.begin(), tmp.end(), std::back_inserter(vec));
		}
		else{
			vec.push_back(dir_path + win32fd.cFileName);
		}
	} while(FindNextFile(handle, &win32fd));

	FindClose(handle);

	return vec;

}


std::vector<std::string> FileUtils::readDirPathBelowDir(std::string path){

	std::vector<std::string> vec;

	WIN32_FIND_DATA win32fd;
	HANDLE handle = FindFirstFile((path + "\\*").c_str(), &win32fd);
	if(handle == INVALID_HANDLE_VALUE){
		return vec;
	}

	do{
		// ディレクトリならvectorに追加後、その中を再帰的に探索
		if((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		   std::string(win32fd.cFileName) != "." &&
		   std::string(win32fd.cFileName) != ".."){
		
			std::string dirPath = path + win32fd.cFileName + "/";
			vec.push_back(dirPath);
			std::vector<std::string> tmp = readDirPathBelowDir(dirPath);
			std::copy(tmp.begin(), tmp.end(), std::back_inserter(vec));
		}
	} while(FindNextFile(handle, &win32fd));

	FindClose(handle);

	return vec;
}


std::string FileUtils::openJson(std::string path, picojson::value& v){

	std::ifstream ifs(path);
	if(!ifs.is_open()){
		return (path + "を開けませんでした");
	}
	return picojson::parse(v, ifs);
}
