#ifndef _Timer_WindowsHeader_
#define _Timer_WindowsHeader_
#include "TimerManager_Windows.hpp"

class Timer_Windows : public Timer {
public:
	TimerManager_Windows& timerManager;
	HANDLE handle;
	void* params;
	TimerCallback callback;

public:
	void destroy() {
		timerManager.destroyTimer(this);
	}

public:
	Timer_Windows(TimerManager_Windows& _timerManager, void* _params, TimerCallback _callback)
		: timerManager(_timerManager), handle(0), params(_params), callback(_callback) {};
};
#endif