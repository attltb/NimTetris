#ifndef _Thread_WindowsHeader_
#define _Thread_WindowsHeader_
#include "ThreadManager_Windows.hpp"

class Thread_Windows : public Thread {
public:
	ThreadManager_Windows& threadManager;
	HANDLE handle;
	void* params;
	ThreadCallback callback;

public:
	void free() {
		CloseHandle(handle);
		delete this;
	}

public:
	Thread_Windows(ThreadManager_Windows& _threadManager, void* _params, ThreadCallback _callback)
		: threadManager(_threadManager), handle(0), params(_params), callback(_callback) {};
};
#endif