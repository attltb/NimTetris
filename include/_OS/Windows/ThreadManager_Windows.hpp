#ifndef _ThreadManager_WindowsHeader_
#define _ThreadManager_WindowsHeader_
#include <Windows.h>
#include "ThreadManager.hpp"
class Thread_Windows;
class ThreadManager_Windows : public ThreadManager {
public:
	void activateManager() {};
	void terminateManager() {};

public:
	Thread* newThread(ThreadCallback callback, void* params);
};
#endif