#ifndef _ThreadManagerHeader_
#define _ThreadManagerHeader_
#include "Thread.hpp"
typedef void(*ThreadCallback) (void*);

class ThreadManager {
public:
	virtual void activateManager() = 0;
	virtual void terminateManager() = 0;

public:
	virtual Thread* newThread(ThreadCallback callback, void* params) = 0;
};
#endif