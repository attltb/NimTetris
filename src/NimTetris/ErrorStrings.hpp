#ifndef _ErrorStringsHeader_
#define _ErrorStringsHeader_
#include <string>
std::string getErrorString_LoadResources_CannotFind(std::string filename);
std::string getErrorString_LoadResources_InvalidFile(std::string filename);
std::string getErrorString_LoadResources_OutOfMemory(std::string filename);
std::string getErrorString_LoadSave_InvalidFile();
std::string getErrorString_LoadSave_OutOfMemory();
std::string getErrorString_SaveSave_CannotCreate();
std::string getErrorString_SaveSave_OutOfMemory();
#endif