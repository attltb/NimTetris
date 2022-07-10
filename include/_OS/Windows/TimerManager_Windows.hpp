#ifndef _TimerManager_WindowsHeader_
#define _TimerManager_WindowsHeader_
#include <Windows.h>
#include "TimerManager.hpp"
class Timer_Windows;
class TimerManager_Windows : public TimerManager {
private:
	HANDLE timerqueue;

public:
	void activateManager();
	void terminateManager();

public:
	Timer* newTimer(TimerCallback callback, void* params, int dueTime, int period);
	void destroyTimer(Timer_Windows* timer);
};
#endif