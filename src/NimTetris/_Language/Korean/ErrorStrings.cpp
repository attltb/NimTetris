#include "ErrorStrings.hpp"
std::string getErrorString_LoadResources_CannotFind(std::string filename) {
	return "파일 \"" + filename + "\"를 찾을 수 없습니다.";
}
std::string getErrorString_LoadResources_InvalidFile(std::string filename) {
	return "파일 \"" + filename + "\"가 올바른 리소스 파일이 아닙니다.";
}
std::string getErrorString_LoadResources_OutOfMemory(std::string filename) {
	return "메모리가 부족합니다. 파일 \"" + filename + "\"를 로드할 수 없습니다.";
}
std::string getErrorString_LoadSave_InvalidFile() {
	return "저장 데이터 파일이 손상되었습니다.";
}
std::string getErrorString_LoadSave_OutOfMemory() {
	return "메모리가 부족합니다. 저장 데이터 파일을 로드할 수 없습니다.";
}
std::string getErrorString_SaveSave_CannotCreate() {
	return "저장 데이터 파일을 생성할 수 없습니다.";
}
std::string getErrorString_SaveSave_OutOfMemory() {
	return "메모리가 부족합니다. 저장 데이터 파일을 생성할 수 없습니다.";
}