#ifndef _TimerManagerHeader_
#define _TimerManagerHeader_
#include "Timer.hpp"
typedef void(*TimerCallback) (void*);

class TimerManager {
public:
	virtual void activateManager() = 0;
	virtual void terminateManager() = 0;

public:
	virtual Timer* newTimer(TimerCallback callback, void* parameter, int dueTime, int period) = 0;
};
#endif