#include "ErrorStrings.hpp"
std::string getErrorString_LoadResources_CannotFind(std::string filename) {
	return "���� \"" + filename + "\"�� ã�� �� �����ϴ�.";
}
std::string getErrorString_LoadResources_InvalidFile(std::string filename) {
	return "���� \"" + filename + "\"�� �ùٸ� ���ҽ� ������ �ƴմϴ�.";
}
std::string getErrorString_LoadResources_OutOfMemory(std::string filename) {
	return "�޸𸮰� �����մϴ�. ���� \"" + filename + "\"�� �ε��� �� �����ϴ�.";
}
std::string getErrorString_LoadSave_InvalidFile() {
	return "���� ������ ������ �ջ�Ǿ����ϴ�.";
}
std::string getErrorString_LoadSave_OutOfMemory() {
	return "�޸𸮰� �����մϴ�. ���� ������ ������ �ε��� �� �����ϴ�.";
}
std::string getErrorString_SaveSave_CannotCreate() {
	return "���� ������ ������ ������ �� �����ϴ�.";
}
std::string getErrorString_SaveSave_OutOfMemory() {
	return "�޸𸮰� �����մϴ�. ���� ������ ������ ������ �� �����ϴ�.";
}