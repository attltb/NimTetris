#ifndef _NimTetris_
#define _NimTetris_
#include "ThreadManager.hpp"
#include "TimerManager.hpp"
#include "Game.hpp"
#include "ResourceCollection.hpp"
#include "NimTMessageHandler.hpp"
#include "NimTetrisAutosaveds.hpp"
class NimTetris : public Game {
	ThreadManager& threadManager;
	TimerManager& timerManager;

private:
	ResourceCollection resources;
	NimTetrisAutosaveds autosaveds;
	NimTMessageHandler winMessageHandler;

public:
	const char* getGameName();
	const char* getWindowTitle();
	int getInitialScreenWidth();
	int getInitialScreenHeight();

public:
	bool initialize(WindowHandle wnd);
	bool finalize(WindowHandle wnd);

public:
	WindowMessageHandler& getWindowMessageHandler();

public:
	NimTetris(ThreadManager& _threadManager, TimerManager& _timerManager) 
		: threadManager(_threadManager), timerManager(_timerManager), winMessageHandler(threadManager, resources, autosaveds) {};
};
#endif