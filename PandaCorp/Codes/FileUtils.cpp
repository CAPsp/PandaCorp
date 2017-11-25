#include "FileUtils.h"

#include <Windows.h>



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