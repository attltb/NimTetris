#include "NimTetris.hpp"
#include "NimTetrisAutosaver.hpp"
#include "Randomizer.hpp"
#include "ErrorStrings.hpp"
#include "NimTetrisAI.hpp"
using namespace std;
const char* NimTetris::getGameName() {
	return "NimTetris";
}
const char* NimTetris::getWindowTitle() {
	return "Nim Tetris";
}
int NimTetris::getInitialScreenWidth() {
	return 450;
}
int NimTetris::getInitialScreenHeight() {
	return 450;
}

bool NimTetris::initialize(WindowHandle wnd) {
	ResourceCollection::ERR_CODE errNo = resources.load("Nim Tetris.dat");
	if (errNo!= ResourceCollection::ERR_CODE::OK) {
		if (errNo == ResourceCollection::ERR_CODE::FILE_NOT_EXIST) wnd.msgError(getErrorString_LoadResources_CannotFind("Nim Tetris.dat"));
		if (errNo == ResourceCollection::ERR_CODE::FILE_INVALID) wnd.msgError(getErrorString_LoadResources_InvalidFile("Nim Tetris.dat"));
		if (errNo == ResourceCollection::ERR_CODE::OUT_OF_MEMORY) wnd.msgError(getErrorString_LoadResources_OutOfMemory("Nim Tetris.dat"));
		return false;
	}

	NimTetrisAutosaveds::initialize();
	NimTetrisAutosaver::ERR_CODE errNo2 = NimTetrisAutosaver().load(autosaveds, "data.dat");
	if (errNo2 != NimTetrisAutosaver::ERR_CODE::OK) {
		if (errNo2 == NimTetrisAutosaver::ERR_CODE::FILE_INVALID) wnd.msgError(getErrorString_LoadSave_InvalidFile());
		if (errNo2 == NimTetrisAutosaver::ERR_CODE::OUT_OF_MEMORY) wnd.msgError(getErrorString_LoadSave_OutOfMemory());
		if (errNo2 != NimTetrisAutosaver::ERR_CODE::FILE_NOT_EXIST) return false;
	}

	Randomizer::initialize();
	NimTetrisAI::initialize();
	return true;
}
bool NimTetris::finalize(WindowHandle wnd) {
	resources.unload();

	NimTetrisAutosaver::ERR_CODE errNo2 = NimTetrisAutosaver().save(autosaveds, "data.dat");
	if (errNo2 != NimTetrisAutosaver::ERR_CODE::OK) {
		if (errNo2 == NimTetrisAutosaver::ERR_CODE::FILE_NOT_EXIST) wnd.msgError(getErrorString_SaveSave_CannotCreate());
		if (errNo2 == NimTetrisAutosaver::ERR_CODE::OUT_OF_MEMORY) wnd.msgError(getErrorString_SaveSave_OutOfMemory());
		return false;
	}
	return true;
}

WindowMessageHandler& NimTetris::getWindowMessageHandler() {
	return winMessageHandler;
}