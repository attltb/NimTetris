#include "ErrorStrings.hpp"
std::string getErrorString_LoadResources_CannotFind(std::string filename) {
	return "Cannot fine file \"" + filename + "\".";
}
std::string getErrorString_LoadResources_InvalidFile(std::string filename) {
	return "File \"" + filename + "\" is not a valid resource collection file.";
}
std::string getErrorString_LoadResources_OutOfMemory(std::string filename) {
	return "Out of memory. Cannot load file \"" + filename + "\".";
}
std::string getErrorString_LoadSave_InvalidFile() {
	return "Autosaved file is corrupted.";
}
std::string getErrorString_LoadSave_OutOfMemory() {
	return "Out of memory. Cannot load autosaved file.";
}
std::string getErrorString_SaveSave_CannotCreate() {
	return "Cannot create autosaved file.";
}
std::string getErrorString_SaveSave_OutOfMemory() {
	return "Out of memory. Cannot create autosaved file.";
}