#ifndef _GameHeader_
#define _GameHeader_
#include "WindowHandle.hpp"
#include "WindowMessageHandler.hpp"
class Game {
public:
	virtual const char* getGameName() = 0;
	virtual const char* getWindowTitle() = 0;
	virtual int getInitialScreenWidth() = 0;
	virtual int getInitialScreenHeight() = 0;

public:
	virtual bool initialize(WindowHandle wnd) = 0;
	virtual bool finalize(WindowHandle wnd) = 0;

public:
	virtual WindowMessageHandler& getWindowMessageHandler() = 0;

public:
	virtual ~Game() {};
};
#endif